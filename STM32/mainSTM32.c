#include <stdint.h>
#include "registros.h"
volatile int led_activo = 0;

void USART2_SendChar(char c) {
    while (!(USART2_SR & (1 << 7)));
    USART2_DR = c;
}

void USART2_SendString(const char *str) {
    while (*str) {
        USART2_SendChar(*str++);
    }
}

char USART2_ReceiveChar(void) {
    while (!(USART2_SR & (1 << 5)));
    return (char)(USART2_DR & 0xFF);
}

void enviar_int(int n) {
    char buf[12];
    int i = 0;
    int temp = n;
    char t;
    int j;

    if (temp == 0) {
        USART2_SendChar('0');
        return;
    }
    do {
        buf[i++] = '0' + (temp % 10);
        temp /= 10;
    } while (temp > 0);

    for (j = 0; j < i/2; j++) {
        t = buf[j];
        buf[j] = buf[i-1-j];
        buf[i-1-j] = t;
    }
    buf[i] = '\0';
    USART2_SendString(buf);
}

void recibir_linea(char *buf) {
    int i = 0;
    char c;
    while (1) {
        c = USART2_ReceiveChar();
        if (c == '\n' || c == '\r') break;
        if (i < 31) buf[i++] = c;
    }
    buf[i] = '\0';
}

void calcular_cambio(int cambio) {
    int monedas[] = {200, 100, 50, 20, 10, 5, 2, 1};
    int valores[]  = {200, 100, 50, 20, 10, 5, 2, 1};
    int i, cantidad;
    int primero = 1;

    for (i = 0; i < 8; i++) {
        cantidad = cambio / valores[i];
        if (cantidad > 0) {
            if (!primero) USART2_SendChar(',');
            enviar_int(cantidad);
            USART2_SendChar('x');
            enviar_int(monedas[i]);
            cambio -= cantidad * valores[i];
            primero = 0;
        }
    }
    USART2_SendChar('\n');
}

void parsear_tres(char *buf, int *n1, int *n2, int *n3) {
    char *p = buf;
    *n1 = 0; *n2 = 0; *n3 = 0;
    while (*p >= '0' && *p <= '9') *n1 = *n1*10 + (*p++ - '0');
    if (*p == ';') p++;
    while (*p >= '0' && *p <= '9') *n2 = *n2*10 + (*p++ - '0');
    if (*p == ';') p++;
    while (*p >= '0' && *p <= '9') *n3 = *n3*10 + (*p++ - '0');
}

void apagar_led(void) {
    led_activo = 0;
    GPIOA_ODR &= ~(1 << 5);
}

void USART2_Procesar(void) {
    char buf[32];
    int n1, n2, n3;
    int acumulado;

    while (1) {
        recibir_linea(buf);
        parsear_tres(buf, &n1, &n2, &n3);
        if (n1 == 0 && n2 == 0 && n3 == 0) {
            if (!(GPIOC_IDR & (1 << 13))) {
                USART2_SendString("CANCEL\n");
            } else {
                USART2_SendString("OK_BTN\n");
            }
            continue;
        }
        if (n1 == 9 && n2 == 9 && n3 == 9) {
        	apagar_led();
            USART2_SendString("OFF\n");
            continue;
        }
        if (n1 == 8 && n2 == 8 && n3 == 8) {
            led_activo = 1;
            USART2_SendString("START\n");
            continue;
        }
        if (n3 == 0) {
        	apagar_led();
            enviar_int(n1 * n2);
            USART2_SendChar('\n');
        } else {
            // Modo monedero: LED parpadeando
            led_activo = 1;

            if (!(GPIOC_IDR & (1 << 13))) {
            	apagar_led();
                USART2_SendString("CANCEL\n");
                continue;
            }
            acumulado = n2 + n1;
            if (acumulado >= n3) {
            	apagar_led();
                USART2_SendString("OK;");
                enviar_int(acumulado - n3);
                USART2_SendChar(';');
                calcular_cambio(acumulado - n3);
            } else {
                USART2_SendString("SIGUE;");
                enviar_int(acumulado);
                USART2_SendChar('\n');
            }
        }
    }
}


void TIM2_Init(void) {
    // Activar reloj TIM2
    RCC_APB1ENR |= RCC_APB1ENR_TIM2;

    // Prescaler: 8MHz / 8000 = 1000 Hz
    TIM2_PSC = 7999;

    // Auto-reload: 1000 / 500 = 2 Hz -> parpadeo cada 500ms
    TIM2_ARR = 499;

    // Habilitar interrupcion por update
    TIM2_DIER |= (1 << 0);

    // Activar TIM2 en NVIC (IRQ28)
    NVIC_ISER0 |= (1 << 28);

    // Arrancar el timer
    TIM2_CR1 |= (1 << 0);
}

// Handler de la interrupcion del TIM2
void TIM2_IRQHandler(void) {
    if (TIM2_SR & (1 << 0)) {
        TIM2_SR &= ~(1 << 0); // limpiar flag
        if (led_activo) {
            GPIOA_ODR ^= (1 << 5); // toggle LED
        }
    }
}

int main(void) {
    RCC_APB2ENR |= (1 << 2);
    RCC_APB2ENR |= (1 << 4);
    RCC_APB1ENR |= (1 << 17);

    GPIOA_CRL &= ~(0xFF << 8);
    GPIOA_CRL |=  (0xB  << 8);
    GPIOA_CRL |=  (0x4  << 12);

    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x4 << 20);

    USART2_BRR  = 0x341;
    USART2_CR1 |= (1 << 3);
    USART2_CR1 |= (1 << 2);
    USART2_CR1 |= (1 << 13);
    // PA5 LED salida push-pull 2MHz
    GPIOA_CRL &= ~(0xF << 20);
    GPIOA_CRL |=  (0x2 << 20);

    // Inicializar timer
    TIM2_Init();

    USART2_Procesar();
    return 0;
}

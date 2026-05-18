#ifndef REGISTROS_H
#define REGISTROS_H

#include <stdint.h>

// Direcciones base
#define RCC_BASE    0x40021000
#define GPIOA_BASE  0x40010800
#define GPIOC_BASE  0x40011000
#define USART2_BASE 0x40004400

// RCC
#define RCC_APB2ENR  (*(volatile uint32_t *)(RCC_BASE   + 0x18))
#define RCC_APB1ENR  (*(volatile uint32_t *)(RCC_BASE   + 0x1C))

// GPIOA
#define GPIOA_CRL    (*(volatile uint32_t *)(GPIOA_BASE + 0x00))

// GPIOC
#define GPIOC_CRH    (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_IDR    (*(volatile uint32_t *)(GPIOC_BASE + 0x08))

// USART2
#define USART2_SR    (*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_DR    (*(volatile uint32_t *)(USART2_BASE + 0x04))
#define USART2_BRR   (*(volatile uint32_t *)(USART2_BASE + 0x08))
#define USART2_CR1   (*(volatile uint32_t *)(USART2_BASE + 0x0C))

// GPIOA ODR
#define GPIOA_ODR    (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))

// TIM2
#define TIM2_BASE    0x40000000
#define TIM2_CR1     (*(volatile uint32_t *)(TIM2_BASE + 0x00))
#define TIM2_DIER    (*(volatile uint32_t *)(TIM2_BASE + 0x0C))
#define TIM2_SR      (*(volatile uint32_t *)(TIM2_BASE + 0x10))
#define TIM2_PSC     (*(volatile uint32_t *)(TIM2_BASE + 0x28))
#define TIM2_ARR     (*(volatile uint32_t *)(TIM2_BASE + 0x2C))

// RCC TIM2
#define RCC_APB1ENR_TIM2  (1 << 0)

// NVIC
#define NVIC_ISER0   (*(volatile uint32_t *)0xE000E100)

#endif

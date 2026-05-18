cmake_minimum_required(VERSION 4.1)
project(Proyecto_Definitivo C)

set(CMAKE_C_STANDARD 11)

add_executable(Proyecto_Definitivo main.c
        Menus.c
        LecturaSegura.c
        Administrador.c
        SerialPC.c
        Config.c)

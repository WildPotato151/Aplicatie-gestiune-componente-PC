cmake_minimum_required(VERSION 3.28)
project(Aplicatie_gestiune_componente_PC)

set(CMAKE_CXX_STANDARD 17)

add_executable(Aplicatie_gestiune_componente_PC main.cpp
        Clase/Componenta.cpp
        Clase/Componenta.h)

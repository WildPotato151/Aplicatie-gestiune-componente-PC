cmake_minimum_required(VERSION 3.28)
project(Aplicatie_gestiune_componente_PC)

set(CMAKE_CXX_STANDARD 17)

add_executable(Aplicatie_gestiune_componente_PC main.cpp
        Clase/Componenta.cpp
        Clase/Componenta.h
        Clase/Client.cpp
        Clase/Client.h
        Clase/AdministrareComponenta.cpp
        Clase/AdministrareComponenta.h
        Clase/Validari.h
        Clase/Cont.cpp
        Clase/Cont.h
        Clase/AdministrareConturi.cpp
        Clase/AdministrareConturi.h
        Clase/CumparaComponenta.cpp
        Clase/CumparaComponenta.h
        Clase/AdministrareCumparare.cpp
        Clase/AdministrareCumparare.h)

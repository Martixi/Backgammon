cmake_minimum_required(VERSION 3.26)
project(Backgammon)

set(CMAKE_CXX_STANDARD 17)

add_link_options(-static -static-libgcc -static-libstdc++)

add_executable(Backgammon main.cpp
        conio2.cpp
        conio2.h
        GameBoard/Board.cpp
        GameBoard/Board.h
        GameBoard/Board.cpp
        GameBoard/Visuals.h
        GameBoard/Visuals.cpp
        Defines.h
        Mechanics/Mechanics.cpp
        Mechanics/Mechanics.h
        Other/Other.cpp
        Other/Other.h
        Mechanics/players.h
        Mechanics/players.cpp
        Mechanics/Tokens.cpp
        Mechanics/Tokens.h
        Controls/User_Input.cpp

)

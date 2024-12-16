cmake_minimum_required(VERSION 3.29)
project(prpr)

set(CMAKE_CXX_STANDARD 20)

add_executable(prpr main.c
        user.c
        user.h
        spaceship.h
        spaceship.c
        auxiliar.h
        auxiliar.c
        test.c
        TEST_spaceship.c
        interface.c
        interface.h
        crew.c
        crew.h
        project.c
        project.h
        voyage.c
        voyage.h
        readData/readData.c
        readData/readData.h
)

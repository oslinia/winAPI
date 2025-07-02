cmake_minimum_required(VERSION 3.31)
project(winAPI C)

set(CMAKE_C_STANDARD 11)

add_executable(CollectMenu WIN32 src/CollectMenu/main.c
        src/CollectMenu/header.h
        src/CollectMenu/procedure.c
        src/CollectMenu/resource/main.rc)

add_executable(MenuRc WIN32 src/MenuRc/main.c
        src/MenuRc/header.h
        src/MenuRc/procedure.c
        src/MenuRc/resource/main.rc)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/public)

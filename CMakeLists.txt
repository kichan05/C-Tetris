cmake_minimum_required(VERSION 3.27)
project(C_Tetris C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Tetris main.c
        common/color.h
        common/color.c
        common/util.c
        common/util.h
        common/key.c
        common/key.h
        ui.h
        ui.c
        block.c
        block.h
        config.h
        scene/mainScene.c
        scene/mainScene.h
        scene/initScene.c
        scene/initScene.h
        scene/gameResultScene.c
        scene/gameResultScene.h
)

﻿cmake_minimum_required(VERSION 3.12)
project(sk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SUPPRESS_REGENERATION ON)

set(PFD_INCLUDE_DIRS "lib/portable-file-dialogs")
set(RAYLIB_INCLUDE_DIRS "lib/raylib/src/external")
set(IMGUI_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/lib/imgui")
set(GLM_INCLUDE_DIRS "lib/glm/glm")
set(LIBS "raylib")

file(GLOB IMGUI_SOURCES ${CMAKE_CURRENT_SOURCE_DIR} "lib/imgui/*.cpp")
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
set(SOURCES ${SOURCES} ${IMGUI_SOURCES})

add_subdirectory(lib/raylib)

if (WIN32)
    set(LIBS ${LIBS} imm32)
    set(EXE_ADD WIN32)
endif ()

include_directories(
    "src/"
    ${IMGUI_INCLUDE_DIRS}
    ${RAYLIB_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${PFD_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${EXE_ADD} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    # target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic)
    target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG=1)
    target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_SOURCE_DIR}/res/")
endif()
if (CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(${PROJECT_NAME} PUBLIC RELEASE=1)
    target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="res/")

    # Copy res dir
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res"
        "${CMAKE_CURRENT_BINARY_DIR}/res"
    )
endif()

cmake_minimum_required(VERSION 3.5)
project(tinto_tutorial)

set(TINTO_BASE "${PROJECT_SOURCE_DIR}/..")
set(TINTO_INCLUDE "${TINTO_BASE}/include")
set(TINTO_LIB "${TINTO_BASE}/lib")
set(TINTO_THIRD_PARTY "${TINTO_BASE}/third-party")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DDESKTOP")

include_directories(
        ${TINTO_INCLUDE}
        ${TINTO_THIRD_PARTY}/build/include/SDL2
        ${TINTO_THIRD_PARTY}/build/include/SDL2_image
        ${TINTO_THIRD_PARTY}/build/include/SDL2_mixer
        ${TINTO_THIRD_PARTY}/build/include/SDL2_ttf
)

link_directories(
        ${TINTO_THIRD_PARTY}/build/lib
        ${TINTO_LIB}
)

file(GLOB SOURCE_FILES
    src/*.h
    src/*.cpp
)

add_executable(tinto_tutorial ${SOURCE_FILES})

target_link_libraries(tinto_tutorial
        tinto
)
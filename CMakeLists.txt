cmake_minimum_required(VERSION 3.5)
project(tinto)

set(TINTO_BASE "${PROJECT_SOURCE_DIR}")
set(TINTO_SRC "${TINTO_BASE}/src")
set(TINTO_INCLUDE "${TINTO_BASE}/include")
set(TINTO_THIRD_PARTY "${TINTO_BASE}/third-party")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DDESKTOP")

include_directories(
        ${TINTO_INCLUDE}
        ${TINTO_THIRD_PARTY}/build/include/SDL2
        ${TINTO_THIRD_PARTY}/build/include/SDL2_image
        ${TINTO_THIRD_PARTY}/build/include/SDL2_mixer
        ${TINTO_THIRD_PARTY}/build/include/SDL2_ttf
)

link_directories(${TINTO_THIRD_PARTY}/build/lib)

file(GLOB SOURCE_FILES
        ${TINTO_INCLUDE}/tinto/utils/*.h
        ${TINTO_INCLUDE}/tinto/graphics/*.h
        ${TINTO_INCLUDE}/tinto/engine/*.h
        ${TINTO_INCLUDE}/tinto/easing/*.h
        ${TINTO_INCLUDE}/tinto/anim/*.h
        ${TINTO_INCLUDE}/tinto/audio/*.h
        ${TINTO_INCLUDE}/tinto/scenes/*.h
        ${TINTO_INCLUDE}/tinto/*.h

        ${TINTO_SRC}/utils/*.cpp
        ${TINTO_SRC}/graphics/*.cpp
        ${TINTO_SRC}/engine/*.cpp
        ${TINTO_SRC}/easing/*.cpp
        ${TINTO_SRC}/anim/*.cpp
        ${TINTO_SRC}/audio/*.cpp
        ${TINTO_SRC}/scenes/*.cpp
        ${TINTO_SRC}/scenes/shared/*.cpp
        ${TINTO_SRC}/scenes/splash/*.cpp
        ${TINTO_SRC}/scenes/scan/*.cpp
        ${TINTO_SRC}/scenes/play/*.cpp
        ${TINTO_SRC}/model/*.cpp
        ${TINTO_SRC}/camera/*.cpp
        ${TINTO_SRC}/camera/dummy/*.cpp
        ${TINTO_SRC}/main.cpp
)

set(LIBRARIES
        SDL2
        SDL2_image
        SDL2_mixer
        SDL2_ttf
)

add_library(tinto SHARED ${SOURCE_FILES})

target_link_libraries(tinto ${LIBRARIES})
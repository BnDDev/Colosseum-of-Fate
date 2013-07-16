project(CoF)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST} "bnd.h")

set(CMAKE_CXX_FLAGS "-std=c++11 -static-libstdc++ -mwindows")

#SDL2
find_path(SDL_INCLUDE_DIR SDL2/SDL.h PATHS "C:/MinGW/include")
find_library(SDL_LIBRARY SDL2 PATHS "C:/MinGW/lib")
include_directories(${SDL_INCLUDE_DIR})
set(LIBS ${LIBS} ${SDL_LIBRARY})

target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2 opengl32 SDL2_image)

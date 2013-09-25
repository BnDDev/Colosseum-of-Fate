cmake_minimum_required(VERSION 2.8)
#message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")

project(CoF.bin)
file(GLOB SOURCE_FILES "[a-zA-Z]*.h" "[a-zA-Z]*.hpp" "[a-zA-Z]*.c" "[a-zA-Z]*.cpp")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
#add_executable(${PROJECT_NAME} "main.cpp" "cof.cpp" "log.cpp" "glfunctions.cpp" "bnd.h")

#Find libraries
set(SEARCH_PATHS_INC "C:/MinGW/include" "/Library/Frameworks")
set(SEARCH_PATHS_LIB "C:/MinGW/lib" "/Library/Frameworks")

#SDL2
find_path(SDL_INCLUDE_DIR SDL2/SDL.h PATHS ${SEARCH_PATHS_INC})
find_library(SDL_LIBRARY SDL2 PATHS ${SEARCH_PATHS_LIB})
set(INCS ${INCS} ${SDL_INCLUDE_DIR})
set(LIBS ${LIBS} ${SDL_LIBRARY})

#OpenGL
find_path(OPENGL_INCLUDE_DIR gl.h PATHS ${SEARCH_PATHS_INC})
find_library(OPENGL_LIBRARY OpenGL PATHS ${SEARCH_PATHS_LIB})
set(INCS ${INCS} ${OPENGL_INCLUDE_DIR})
set(LIBS ${LIBS} ${OPENGL_LIBRARY})


set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -Wno-comment")

if(WIN32)
	set(CMAKE_CXX_LINK_FLAGS "-mwindows")
endif(WIN32)

#target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2 opengl32 SDL2_image)
target_link_libraries(${PROJECT_NAME} ${LIBS})
include_directories(${INCS})

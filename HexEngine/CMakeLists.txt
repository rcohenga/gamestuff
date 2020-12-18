cmake_minimum_required(VERSION 3.7)

project(HexEngine)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_library(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
	PUBLIC
	sfml-graphics
	sfml-window)
	
target_include_directories(${PROJECT_NAME}
	PUBLIC
	src/Coordinates
	
	src/Clickable
	src)
	
add_subdirectory(test)
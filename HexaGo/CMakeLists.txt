cmake_minimum_required(VERSION 3.7)

project(HexaGo)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
	sfml-graphics
	sfml-window
	
	HexEngine)
	
target_include_directories(${PROJECT_NAME}
	PUBLIC
	src)
cmake_minimum_required(VERSION 3.7)

project(HexEngineNetwork)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_library(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
	PUBLIC
	sfml-network)
	
target_include_directories(${PROJECT_NAME}
	PUBLIC
	src)
cmake_minimum_required(VERSION 3.7)

project(${PROJECT_NAME}_test)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
	HexEngine)
	
target_include_directories(${PROJECT_NAME}
	PUBLIC
	src)
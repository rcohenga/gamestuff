cmake_minimum_required(VERSION 3.7)

project(NetworkingPOC_client)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
	HexEngineNetwork)
	
target_include_directories(${PROJECT_NAME}
	PUBLIC
	src)
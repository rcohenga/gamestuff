project(gamestuff)

cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(SFML)

add_subdirectory(HexEngine)
add_subdirectory(HexaGo)

add_subdirectory(NetworkingPOC)
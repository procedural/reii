project(00_Command_List C)
cmake_minimum_required(VERSION 2.8.12)
add_executable(${PROJECT_NAME} main.c ../reii/reii.c)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/../glfw/lib/libglfw.so.3 -lGL)

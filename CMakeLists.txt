cmake_minimum_required(VERSION 3.12)
project(Zadanie_3 VERSION 1.0.0)

add_executable(${PROJECT_NAME} src/main.cpp src/board.cpp src/functions.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/inc/
)
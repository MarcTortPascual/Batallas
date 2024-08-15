cmake_minimum_required(VERSION 3.26.4)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-12")
project(RPG DESCRIPTION "Juego" LANGUAGES CXX)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
add_executable(${PROJECT_NAME} 
    ${PROJECT_SOURCE_DIR}/src/Boton.cpp 
    ${PROJECT_SOURCE_DIR}/src/Enemigo.cpp 
    ${PROJECT_SOURCE_DIR}/src/main.cpp 
    ${PROJECT_SOURCE_DIR}/src/Personaje.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2_image)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2_ttf)
cmake_minimum_required(VERSION 3.16)
project(breakout)

set(CMAKE_C_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

file(GLOB SOURCES "src/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE include)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_TTF_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} m)
target_link_libraries(${PROJECT_NAME} ${SDL2_MIXER_LIBRARIES} m)
target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES} m)

file(COPY data DESTINATION ${CMAKE_BINARY_DIR})

cmake_minimum_required (VERSION 2.6)
project (Push_button)
include_directories(${PROJECT_SOURCE_DIR}/h)
add_executable(Push_button c/window.c c/button.c)

#Lookup and add sdl2 for input and output
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
  )
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
file(COPY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


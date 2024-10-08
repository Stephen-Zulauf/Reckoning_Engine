#minimum required cmake version
#cmake --version

cmake_minimum_required(VERSION 3.2)

#set project name
project (Reckoning_Engine)

find_package(SDL2 REQUIRED)

#create sources variable
set(SOURCES
  main.cpp
  src/Renderer.cpp
  src/Window.cpp
)

#add excutable with sources
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} SDL2)

#directories included
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib
  )

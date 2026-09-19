# Минимально требуемая версия CMake
cmake_minimum_required(VERSION 3.14)

project(pyramid_app VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Выходные директории для бинарников и библиотек
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(APP_utils INTERFACE)

# Создание исполняемого файла из исходных кодов
target_include_directories(APP_utils INTERFACE "${CMAKE_SOURCE_DIR}/Src/include")


add_executable(pyramid_app "${CMAKE_SOURCE_DIR}/Src/code/main.cpp")
target_link_libraries(pyramid_app PRIVATE APP_utils)



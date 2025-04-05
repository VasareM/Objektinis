cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Objektinis)


# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(Include)

# Add the executable
add_executable(Objektinis
    kodas_vektoriai.cpp
    funkcijos.cpp
)

# Copy data files after build
add_custom_command(TARGET Objektinis POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_SOURCE_DIR}/kursiokai.txt"
    "${CMAKE_SOURCE_DIR}/sukurtas_studentai1000.txt"
    "${CMAKE_SOURCE_DIR}/sukurtas_studentai10000.txt"
    "${CMAKE_SOURCE_DIR}/sukurtas_studentai100000.txt"
    "${CMAKE_SOURCE_DIR}/sukurtas_studentai1000000.txt"
    "${CMAKE_SOURCE_DIR}/sukurtas_studentai10000000.txt"
    "${CMAKE_BINARY_DIR}/debug/"
)


#file(GLOB SOURCES "src/*.cpp")


# Include directories
#target_include_directories(Objektinis PUBLIC "${PROJECT_SOURCE_DIR}")

# Link libraries (if any)
# target_link_libraries(Objektinis <library_name>)

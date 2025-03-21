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

#file(GLOB SOURCES "src/*.cpp")


# Include directories
#target_include_directories(Objektinis PUBLIC "${PROJECT_SOURCE_DIR}")

# Link libraries (if any)
# target_link_libraries(Objektinis <library_name>)

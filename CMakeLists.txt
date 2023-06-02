cmake_minimum_required(VERSION 3.5)

# Set the project name and version
project(VulkanSceneGraphTest VERSION 1.0)

# Set the C++ standard (change if necessary)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your source files here
set(SOURCES
    "src/main.cpp"
    "src/core/properties/PropertyGroup.cpp"
    "src/core/properties/PropertyChangeListener.cpp"
    "src/core/exceptions/EmitException.cpp"
)

# Add an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Set any additional compiler flags or options
# For example, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
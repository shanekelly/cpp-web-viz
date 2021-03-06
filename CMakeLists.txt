# Set the minimum required version of CMake.
cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE Release)

# Set the project name.
project(CppWebViz)

# Specify that the code should be compiled for C++20.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source directory to the include path so that header files can be included relative to the
# source directory. Also add thirdparty paths that we will need to include header files from.
include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/thirdparty/websocketpp
  ${PROJECT_SOURCE_DIR}/thirdparty/json/single_include
)

# Add directories, so that CMake knows to recurse down into them to build their contents.
add_subdirectory(cpp_web_viz)
add_subdirectory(examples)
add_subdirectory(thirdparty)

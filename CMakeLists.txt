cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

## Use -std=c++14 as default.
set(CMAKE_CXX_STANDARD 14)
## Disable C++ extensions
set(CMAKE_CXX_EXTENSIONS OFF)
## Require full C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(jHElib_jni_example
       	LANGUAGES CXX)
include_directories(/Library/Java/JavaVirtualMachines/jdk1.8.0_45.jdk/Contents/Home/include/)
include_directories(/Library/Java/JavaVirtualMachines/jdk1.8.0_45.jdk/Contents/Home/include/darwin/)
find_package(helib 1.0.0 EXACT REQUIRED)

set(SRC helibwrapper.cpp)                                                      
add_library(helibjni SHARED ${SRC})  
target_link_libraries(helibjni helib)


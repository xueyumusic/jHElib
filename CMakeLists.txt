cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

## Use -std=c++14 as default.
set(CMAKE_CXX_STANDARD 14)
## Disable C++ extensions
set(CMAKE_CXX_EXTENSIONS OFF)
## Require full C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED ENV{JAVA_HOME})
    message(FATAL_ERROR "not defined environment variable:JAVA_HOME") 
endif()

project(jHElib_jni_example
       	LANGUAGES CXX)
## include_directories(/Library/Java/JavaVirtualMachines/jdk1.8.0_241.jdk/Contents/Home/include/)
## include_directories(/Library/Java/JavaVirtualMachines/jdk1.8.0_241.jdk/Contents/Home/include/darwin/)

include_directories($ENV{JAVA_HOME}/include/)
include_directories($ENV{JAVA_HOME}/include/darwin/)

find_package(helib)

set(SRC helibwrapper.cpp)                                                      
add_library(helibjni SHARED ${SRC})  
target_link_libraries(helibjni helib)


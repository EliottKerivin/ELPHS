cmake_minimum_required(VERSION 3.31.6...4.3.0)
project(ELPHS C)
set(CMAKE_C_STANDARD 23)

include(CTest)
find_package(Doxygen)
if(Doxygen_FOUND)
 add_subdirectory(docs)
endif()

add_subdirectory(libalgea)

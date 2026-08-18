cmake_minimum_required(VERSION 4.3.0)
project(ELPHS C)
set(CMAKE_C_STANDARD 23)

include(CTest)
find_package(Doxygen)
if(Doxygen_FOUND)
  include(FetchContent)
    FetchContent_Declare(
      doxygen-awesome-css
      URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/heads/main.zip
  )
  FetchContent_MakeAvailable(doxygen-awesome-css)
  # Save the location the files were cloned into
  # This allows us to get the path to doxygen-awesome.css
  FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)
endif()

add_subdirectory(libalgea)

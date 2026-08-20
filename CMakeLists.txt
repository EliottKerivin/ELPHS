cmake_minimum_required(VERSION 3.31.6...4.3.0)
project(ELPHS C)
set(CMAKE_C_STANDARD 23)

include(CTest)
find_package(Doxygen)
if(Doxygen_FOUND)
  include(FetchContent)
    FetchContent_Declare(
      doxygen-awesome-css
      GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css
      GIT_TAG d52eafe3e9303399fda15661f3d7bb8fe3d7eabc # v2.4.2
  )
  FetchContent_MakeAvailable(doxygen-awesome-css)
  # Save the location the files were cloned into
  # This allows us to get the path to doxygen-awesome.css
  FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)
endif()

add_subdirectory(libalgea)

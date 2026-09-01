add_library(nima STATIC)

target_link_libraries(nima PRIVATE algea)
target_include_directories(nima PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_features(nima PUBLIC c_std_23)

set(sources FDProblem.c abstractProblem.c)
list(TRANSFORM sources PREPEND src/)

target_sources(nima PRIVATE ${sources}) 

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

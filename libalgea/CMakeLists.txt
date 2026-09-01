add_library(algea STATIC)

target_compile_definitions(algea PUBLIC $<$<CONFIG:RELEASE>:ALGEA_NO_BOUNDS_CHECKING>)
# We don't want the implementation to have bounds checking, it's just for external code. 
# Ours is supposed to be safe
target_compile_definitions(algea PRIVATE ALGEA_NO_BOUNDS_CHECKING)
target_compile_features(algea PUBLIC c_std_23)

set(sources matrix.c errors.c tridiagonal.c)
list(TRANSFORM sources PREPEND src/)

target_sources(algea PRIVATE ${sources}) 
target_include_directories(algea PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

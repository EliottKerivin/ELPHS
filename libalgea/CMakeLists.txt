add_library(algea STATIC)

target_compile_definitions(algea PUBLIC $<$<CONFIG:RELEASE>:ALGEA_NO_BOUNDS_CHECKING>)
# We don't want the implementation to have bounds checking, it's just for external code. 
# Ours is supposed to be safe
target_compile_definitions(algea PRIVATE ALGEA_NO_BOUNDS_CHECKING)

set(sources matrix.c errors.c)
list(TRANSFORM sources PREPEND src/)

target_sources(algea PRIVATE ${sources}) 
target_include_directories(algea PUBLIC include)
target_include_directories(algea PRIVATE src)

if(BUILD_TESTING)
  add_executable(matrix.basicTests tests/matrix.basicTests.c)
  target_link_libraries(matrix.basicTests PRIVATE algea)
  add_test(NAME "Matrix basics" COMMAND matrix.basicTests)

  add_executable(matrix.mathTests tests/matrix.mathTests.c)
  target_link_libraries(matrix.mathTests PRIVATE algea)
  add_test(NAME "Matrix math" COMMAND matrix.mathTests)
endif()

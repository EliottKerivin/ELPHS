add_library(algea STATIC)

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

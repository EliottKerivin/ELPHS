add_library(algea STATIC)

set(sources matrix.c)
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

if(Doxygen_FOUND)
  set(DOXYGEN_PROJECT_NAME algea)
  set(DOXYGEN_EXTRACT_STATIC YES)
  set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
  set(DOXYGEN_REPEAT_BRIEF NO)
  set(DOXYGEN_SHOW_FILES NO)
  set(DOXYGEN_SORT_MEMBER_DOCS NO)
  set(DOXYGEN_HTML_EXTRA_STYLESHEET "${AWESOME_CSS_DIR}/doxygen-awesome.css")
  doxygen_add_docs(algea-docs "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif()

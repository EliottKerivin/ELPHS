add_executable(matrix.basicTests matrix.basicTests.c)
target_link_libraries(matrix.basicTests PRIVATE algea)
add_test(NAME "Matrix basics" COMMAND matrix.basicTests)

add_executable(matrix.mathTests matrix.mathTests.c)
target_link_libraries(matrix.mathTests PRIVATE algea)
add_test(NAME "Matrix math" COMMAND matrix.mathTests)

add_executable(tridiagonal.tests tridiagonal.tests.c)
target_link_libraries(tridiagonal.tests PRIVATE algea)
add_test(NAME "Triadiagonal tests" COMMAND tridiagonal.tests)

add_executable(operations.tests operations.tests.c)
target_link_libraries(operations.tests PRIVATE algea)
add_test(NAME "Mixed operations" COMMAND operations.tests)

add_executable(abstractProblem.tests nimaAbstractTests.c)
target_link_libraries(abstractProblem.tests PRIVATE nima)
target_include_directories(abstractProblem.tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../src")

add_test(NAME "Abstract formulation" COMMAND abstractProblem.tests)

add_executable(FDProblem.test nimaFDtests.c)
target_link_libraries(FDProblem.test PRIVATE nima)
target_include_directories(FDProblem.test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../src")

add_test(NAME "Finite differences" COMMAND FDProblem.test)

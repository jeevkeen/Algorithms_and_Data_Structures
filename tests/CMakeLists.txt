create_executable_project(AllTests)
target_link_libraries(AllTests gtest gtest_main EasyExample StackOnMassLib)
target_include_directories(AllTests PRIVATE ${CMAKE_SOURCE_DIR}/lib_easy_example ${CMAKE_SOURCE_DIR}/StackOnMassLib)
add_test(NAME AllTests COMMAND AllTests)
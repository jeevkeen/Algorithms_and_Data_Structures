create_executable_project(AllTests)
target_link_libraries(AllTests gtest gtest_main EasyExample)
target_include_directories(AllTests PRIVATE ${CMAKE_SOURCE_DIR}/lib_easy_example)
add_test(NAME AllTests COMMAND AllTests)
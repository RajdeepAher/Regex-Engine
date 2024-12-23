cmake_minimum_required(VERSION 3.10)

# Set the project name
project(TestRunner)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add the test folder to the list of source files
file(GLOB TEST_SOURCES test/*.cpp)

set(SOURCES 
    src/lexer.cpp
    src/tokens.cpp
    src/re_ast.cpp
    # Do not include test files here
)

add_executable(run_tests ${SOURCES} test/test_main.cpp)

# Optionally, you can link libraries like Google Test if required
# target_link_libraries(run_tests gtest gtest_main)
add_custom_target(clean_
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}
    #COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning build"
)

# Enable testing functionality
enable_testing()

# Add the test to CTest
add_test(NAME run_tests COMMAND run_tests)


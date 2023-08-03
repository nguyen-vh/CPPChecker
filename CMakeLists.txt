cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Include Catch2 library
add_subdirectory(CPPChecker)

# Add the main executable
add_executable(Main main.cpp)

# Link the main executable with the CPPChecker library
target_link_libraries(Main PRIVATE CPPChecker)

# Add the Catch2 test executable
add_executable(catch2_tests CPPChecker/catch2_Tests/test.cpp)

# Link the Catch2 test executable with the CPPChecker library
target_link_libraries(catch2_tests PRIVATE CPPChecker)

# Enable testing with CTest
enable_testing()

# Add the Catch2 test as a test case
add_test(NAME MyCatch2Test COMMAND catch2_tests)

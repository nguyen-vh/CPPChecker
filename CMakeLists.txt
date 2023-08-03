cmake_minimum_required(VERSION 3.12)

# Set CPP Standard
set(CMAKE_CXX_STANDARD 20)

project(CMake_Catch2Test)

# Add the Main executable
add_executable(Main main.cpp)

# Add the CPPChecker library
add_library(CPPChecker CPPChecker/CPPChecker.cpp)

# Include directories for Main and CPPChecker
target_include_directories(Main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/CPPChecker)

# Link the Main executable with the CPPChecker library
target_link_libraries(Main PRIVATE CPPChecker)

# Add the Catch2 test executable
add_executable(catch2_test CPPChecker/As_header/catch2_Tests/test.cpp)

# Include directories for catch2_test
target_include_directories(catch2_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/CPPChecker)

# Link the catch2_test with the CPPChecker library
target_link_libraries(catch2_test PRIVATE CPPChecker)

# Enable testing with CTest
enable_testing()

# Add a test that runs the catch2_test executable
add_test(NAME Catch2Tests COMMAND catch2_test)

cmake_minimum_required(VERSION 3.10)

#set the project name
project(LinearAlgebraMPI)

#enable modern C++
set(CMAKE_CXX_STANDARD 17)

#add the executable
add_executable(Main.exe main.cpp HypreExample.cpp PETScExample.cpp GenericExample.cpp)

#add subdirectory
add_subdirectory(LocalAlgebra)

target_link_libraries(Main.exe PUBLIC LocalLinearAlgebra)

target_include_directories(Main.exe PUBLIC "${CMAKE_SOURCE_DIR}/LocalAlgebra")

enable_testing()
add_test(Test Main.exe HypreExample.h PETScExample.h GenericExapmle.h)

enable_testing()
find_package(GTest REQUIRED)

add_executable(Test.exe Test.cpp)
target_link_libraries(Test.exe PUBLIC LocalLinearAlgebra GTest::GTest GTest::Main)

target_include_directories(Test.exe PUBLIC "${CMAKE_SOURCE_DIR}/LocalAlgebra")

#Fichier CMakeLists.txt
gtest_discover_tests(Test.exe)

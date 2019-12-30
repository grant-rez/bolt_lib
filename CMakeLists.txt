cmake_minimum_required(VERSION 3.9)

project(bolt 
  VERSION 0.1.0 
  DESCRIPTION "A toy webserver framework by Grant Reszczyk"
  LANGUAGES CXX
)

enable_testing()

add_subdirectory(bolt)
add_subdirectory(demo)
add_subdirectory(tests)
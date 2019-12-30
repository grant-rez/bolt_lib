set(CMAKE_CXX_STANDARD 14)


add_executable(demo src/server.cpp)
target_link_libraries(demo bolt) 

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

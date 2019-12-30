set(CMAKE_CXX_STANDARD 17)
find_package(Catch2 REQUIRED)
find_package(trompeloeil REQUIRED)

aux_source_directory(src UNIT_TEST_LIST)

foreach(FILE IN LISTS UNIT_TEST_LIST)
  string(REPLACE ".test.cpp" "" NAME ${FILE})
  string(REPLACE "src/"  "" NAME ${NAME})
  set(TARGET_NAME tests_${NAME})

  add_executable(${TARGET_NAME}
    main.cpp
    ${FILE}
  )

  add_test(
    NAME ${TARGET_NAME}
    COMMAND ${TARGET_NAME}
  )

  target_include_directories(${TARGET_NAME} PRIVATE ../bolt/src)

  target_link_libraries(${TARGET_NAME} 
    bolt
    Catch2::Catch2
    trompeloeil
  )

endforeach()




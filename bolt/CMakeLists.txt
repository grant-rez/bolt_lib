set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME bolt)

add_library(${TARGET_NAME} STATIC 
  src/bolt.cpp
  src/buffered_reader.cpp
  src/html_page.cpp
  src/http/http_connection_handler_factory.cpp
  src/http/http_request.cpp
  src/http/socket_http_connection_handler.cpp
)

set_target_properties(${TARGET_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${TARGET_NAME} PROPERTIES PUBLIC_HEADER "include/bolt.h;include/http_page.h")

target_include_directories(${TARGET_NAME} PUBLIC include)
target_include_directories(${TARGET_NAME} PUBLIC src)

include(GNUInstallDirs)

install(TARGETS ${TARGET_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

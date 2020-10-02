project(communication)

cmake_minimum_required(VERSION 3.5)

add_library(communication_library)

target_include_directories(communication_library
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_sources(communication_library
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gpio.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/i2c.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pwm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serial.cpp
)

set_target_properties(communication_library
  PROPERTIES
    CXX_STANDARD_REQUIRED 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Werror"
)

find_package(Threads REQUIRED)

target_link_libraries(communication_library
  PUBLIC
    Threads::Threads
)

add_executable(communicate)
target_sources(communicate
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main/main.cpp)
target_link_libraries(communicate communication_library)

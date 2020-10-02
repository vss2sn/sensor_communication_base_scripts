project(communication)

cmake_minimum_required(VERSION 3.5)

# For clang-tidy
string(CONCAT CLANG_TIDY_CHECKS
  "-*,"                                    # enable all1
  # "-modernize-use-trailing-return-type,"  # style-choice
  # "-fuchsia-default-arguments-calls,"     # allow use of default values in constructors
  # "-cert-msc50-cpp,"                      # rand() is good enough for the current usage
  # "-cert-msc30-c,"                        # rand() is good enough for the current usage
  # "-fuchsia-overloaded-operator"          # +, -, () overloaded for node
  # "cppcoreguidelines-pro-bounds-array-to-pointer-decay,"
  # "cppcoreguidelines-avoid-c-arrays"
  "readability-make-member-function-const"
)
set( CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=${CLANG_TIDY_CHECKS}" )

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

if(${CMAKE_VERSION} VERSION_LESS "3.11.0")
    add_executable(communicate) ${CMAKE_CURRENT_SOURCE_DIR}/main/main.cpp)
else()
  add_executable(communicate)
  target_sources(communicate
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main/main.cpp
  )
endif()

target_link_libraries(communicate communication_library)

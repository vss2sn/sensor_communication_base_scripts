project(sensor_communication)

cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++11)

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

set( CXX_FLAGS "-w" )
set( CMAKE_CXX_FLAGS "${CXX_FLAGS}" )

# If building each file with it's own output, set to ON
# If buiding single file (main.cpp) to test any/all protocols, set to OFF
option(BUILD_INDIVIDUAL "BUILD_INDIVIDUAL" ON)

## If ROS OpenCV conflicts with default OpenCV
#option(ROS_OPENCV "ROS_OPENCV" ON)
#if (ROS_OPENCV)
#	find_package(OpenCV REQUIRED NO_MODULE PATHS /usr/local NO_DEFAULT_PATH) 
#	# should be optional, tells CMake to use config mode # look here # and don't look anywhere else
#else (ROS_OPENCV)
#	find_package( OpenCV REQUIRED )
#endif (ROS_OPENCV)

#find_package(CUDA 9.0 REQUIRED)
#find_package( Boost REQUIRED COMPONENTS system filesystem thread timer system chrono )

include_directories( ${CMAKE_SOURCE_DIR}/inc )

file( GLOB LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
file( GLOB LIB_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h )

message( "${Green}Individual files being built:${ColourReset}" )
set(my_list ${LIB_SOURCES})
if (BUILD_INDIVIDUAL)
	#Removing main if building individual
	list(REMOVE_ITEM LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
	add_definitions(-DBUILD_INDIVIDUAL)
	foreach( testsourcefile ${LIB_SOURCES} )
		string( REPLACE ".cpp" ".o" testname ${testsourcefile})
		string( REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/src/" "" testname ${testname} )
		message( ${testname} )
		add_executable( ${testname} ${testsourcefile} ${LIB_HEADERS} )
		target_link_libraries( ${testname} "${OpenCV_LIBS}" "${Boost_LIBRARIES}")# opencv_cudaoptflow opencv_cudaimgproc)
	endforeach( testsourcefile ${LIB_SOURCES} )
else (BUILD_INDIVIDUAL)
	message(main.cpp)
	add_executable( main.o "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp" ${LIB_HEADERS} )
	target_link_libraries( main.o "${OpenCV_LIBS}" "${Boost_LIBRARIES}")# opencv_cudaoptflow opencv_cudaimgproc)
endif (BUILD_INDIVIDUAL)
message( "${Green}End of files being built ${ColourReset}" )



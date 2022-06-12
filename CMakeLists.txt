cmake_minimum_required(VERSION 3.2)
project(Filets)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++20 -g  -march=native -O0")
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")

include_directories(./include)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#
#include_directories(Boost_INC /usr/include/boost)
#set(Boost_USE_STATIC_LIBS ON)
#set(BOOST_COMPONENTS date_time chrono filesystem iostreams
#        program_options regex system thread unit_test_framework)
#find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})




set(LIB_SOUR
	src/ReadBuffer.cc
	src/WriteBuffer.cc
	src/Vecstream.cc
	src/DataPayload.cc
	src/RequestPayload.cc
	src/Recvresponse.cc
	src/Frame.cc
	src/UdpSocket.cc
	src/FiletsServer.cc
	src/FiletsClient.cc
        )

add_library(Filets STATIC ${LIB_SOUR})

set(TAR_LIB
	Filets
	)

add_executable(main main.cc)
target_link_libraries(main ${TAR_LIB})


###########################TESTS########################
add_executable(ReadBuffer tests/ReadBufferTest.cc)
target_link_libraries(ReadBuffer ${TAR_LIB})

add_executable(WriteBuffer tests/WriteBufferTest.cc)
target_link_libraries(WriteBuffer ${TAR_LIB})

add_executable(Payload tests/PayloadTest.cc)
add_dependencies(Payload ${TAR_LIB})
target_link_libraries(Payload ${TAR_LIB})

add_executable(Vecstream tests/VecstreamTest.cc)
target_link_libraries(Vecstream ${TAR_LIB})

add_executable(DataPayload tests/DataPayloadTest.cc)
target_link_libraries(DataPayload ${TAR_LIB})

add_executable(RecvResponsePayload tests/RecvResponseTest.cc)
target_link_libraries(RecvResponsePayload ${TAR_LIB})

add_executable(FrameTest tests/FrameTest.cc)
target_link_libraries(FrameTest ${TAR_LIB})

add_executable(UdpSocketTest tests/UdpSocketTest.cc)
target_link_libraries(UdpSocketTest ${TAR_LIB})

add_executable(FiletsServerTest tests/FiletsServerTest.cc)
target_link_libraries(FiletsServerTest ${TAR_LIB})

add_executable(FiletsClientTest tests/FileClientTest.cc)
target_link_libraries(FiletsClientTest ${TAR_LIB})


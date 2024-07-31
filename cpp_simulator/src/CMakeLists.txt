cmake_minimum_required(VERSION 3.16)

project(LiDARCPP CXX)

ADD_DEFINITIONS(-O3 -W -Wall -D DEBUG)

ADD_SUBDIRECTORY(tx_lidar out/tx_lidar)
ADD_SUBDIRECTORY(rx_lidar out/rx_lidar)
ADD_SUBDIRECTORY(channel_lidar out/channel_lidar)
ADD_SUBDIRECTORY(common out/common)

ADD_EXECUTABLE(LiDARCPP main.cpp)
ADD_EXECUTABLE(LiDARCPPFMCW main_fmcw.cpp)

target_include_directories (LiDARCPP PUBLIC ${CMAKE_SOURCE_DIR}/tx_lidar
			    ${CMAKE_SOURCE_DIR}/rx_lidar
			    ${CMAKE_SOURCE_DIR}/channel_lidar
			    ${CMAKE_SOURCE_DIR}/common )

target_include_directories (LiDARCPPFMCW PUBLIC ${CMAKE_SOURCE_DIR}/tx_lidar
			    ${CMAKE_SOURCE_DIR}/rx_lidar
			    ${CMAKE_SOURCE_DIR}/channel_lidar
			    ${CMAKE_SOURCE_DIR}/common )


TARGET_LINK_LIBRARIES(LiDARCPP tx_lidar rx_lidar channel_lidar common pthread fftw3)
TARGET_LINK_LIBRARIES(LiDARCPPFMCW tx_lidar rx_lidar channel_lidar common pthread fftw3)

INSTALL(TARGETS LiDARCPP DESTINATION ${CMAKE_SOURCE_DIR}/../bin)
INSTALL(TARGETS LiDARCPPFMCW DESTINATION ${CMAKE_SOURCE_DIR}/../bin)


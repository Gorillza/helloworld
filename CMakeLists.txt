cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES main.cpp awgn_generator.cpp qam_modulator.cpp qam_demodulator.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
cmake_minimum_required(VERSION 3.21)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled src/main.cpp src/Candlestick.cpp src/Candlestick.h src/Trading.cpp src/Trading.h src/StocasticOscillator.cpp src/StocasticOscillator.h src/Simulator.cpp src/Simulator.h src/matplotlibcpp.h src/Visualise.cpp src/Visualise.h)

include_directories(vcpkg/packages/jsoncpp_x86-windows/include)

include_directories(C:\\Python310)
include_directories(C:\\Python310\\Lib\\site-packages\\numpy\\core\\include)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(untitled ${PYTHON_LIBRARIES})
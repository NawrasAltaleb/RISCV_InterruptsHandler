cmake_minimum_required(VERSION 3.0)
project(RISCV-TESTING-FRAMEWORK C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ${LLVM_CXX_FLAGS} -fpermissive ")
set(CMAKE_MODULE_LINKER_FLAGS "-L/usr/lib -L/usr/local/lib -rt -dl -tinfo -pthread -z")


set (SYSTEMC_PATH /usr/local/systemc)
include_directories(${SYSTEMC_PATH}/include)
find_library(systemc systemc ${SYSTEMC_PATH}/lib-linux64)
link_directories(${SYSTEMC_PATH}/lib-linux64)

set (SCV_PATH /usr/local/scv)
include_directories(${SCV_PATH}/include)
find_library(scv scv ${SCV_PATH}/lib-linux64)
link_directories(${SCV_PATH}/lib-linux64)

include_directories(${CMAKE_SOURCE_DIR}/RISCV_Testing/ESL/include)

find_package( Boost REQUIRED COMPONENTS iostreams program_options )

# add executables
add_executable(RISCV_test sc_main_test.cpp)

# link libraries
target_link_libraries(RISCV_test systemc)
target_link_libraries(RISCV_test scv)
target_link_libraries(RISCV_test ${Boost_LIBRARIES} pthread)

# add macros
target_compile_definitions(RISCV_test PRIVATE SC_SIMULATE)

cmake_minimum_required (VERSION 2.6)
project (HMMC)

# The version number.
set (HMMC_VERSION_MAJOR 1)
set (HMMC_VERSION_MINOR 0)

# These will make cmake use clang and clang++ instead of gcc and g++
#SET (CMAKE_C_COMPILER             "/usr/bin/clang")
SET (CMAKE_C_FLAGS                "-Wall -std=c99")
SET (CMAKE_C_FLAGS_DEBUG          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

#looks like on OSX the c++ clang compiler is also clang, not clang++
#SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
#SET (CMAKE_CXX_COMPILER             "/opt/local/bin/clang++-mp-3.1")
SET (CMAKE_CXX_FLAGS                "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /opt/local/lib)

set (MPI_COMPILER "/opt/mvapich2-x/gnu/bin/mpic++")
set (MPI_INCLUDE_PATH "/opt/mvapich2-x/gnu/include")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/tao/undvc_common/cmake/Modules/")

find_package(MPI REQUIRED)
set (CMAKE_CXX_COMPILE_FLAGS ${CMAKE_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
#for some reason this line doesn't work on my laptop
#set (CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
include_directories(${MPI_INCLUDE_PATH})

find_package(Boost REQUIRED COMPONENTS system filesystem)

add_subdirectory(tao)

#include_directories (${PROJECT_SOURCE_DIR}/tao/evolutionary_algorithms)
#include_directories (${PROJECT_SOURCE_DIR}/tao/synchronous_algorithms)
include_directories (${PROJECT_SOURCE_DIR}/tao/undvc_common)
include_directories(${PROJECT_SOURCE_DIR}/tao)
include_directories(${Boost_INCLUDE_DIR})

link_directories(${Boost_LIBRARY_DIRS})

add_executable(hmmc main)
target_link_libraries(hmmc ${Boost_SYSTEM_LIBRARY} ${MPI_LIBRARIES} undvc_common asynchronous_algorithms synchronous_algorithms tao_util mpi_algorithms)


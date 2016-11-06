cmake_minimum_required (VERSION 3.1)
project (smali-tools)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
 
# The version number.
set (smali-tools_VERSION_MAJOR 0)
set (smali-tools_VERSION_MINOR 1)
 
# does this system provide the log and exp functions?
 #include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindAntlr2.cmake)
set(ANTLR2_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/antlr/include)
set(ANTLR2_EXECUTABLE ${CMAKE_BINARY_DIR}/antlr/bin/antlr)
set(ANTLR2_LIBARIES ${CMAKE_BINARY_DIR}/antlr/lib/libantlr.a)


find_package(Boost 1.44.0 REQUIRED filesystem system)

add_subdirectory(grammar)
add_subdirectory(test/grammar)




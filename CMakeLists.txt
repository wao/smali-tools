cmake_minimum_required (VERSION 3.0)
project (smali-tools)
include(CTest)
 
# The version number.
set (smali-tools_VERSION_MAJOR 0)
set (smali-tools_VERSION_MINOR 1)
 
# does this system provide the log and exp functions?
include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindAntlr2.cmake)

add_subdirectory(test/grammar)



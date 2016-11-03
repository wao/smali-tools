cmake_minimum_required (VERSION 2.6)
project (smali-tools)
include(CTest)
 
# The version number.
set (smali-tools_VERSION_MAJOR 0)
set (smali-tools_VERSION_MINOR 1)
 
# does this system provide the log and exp functions?
include (${CMAKE_ROOT}/cmake/FindAntlr2.cmake)




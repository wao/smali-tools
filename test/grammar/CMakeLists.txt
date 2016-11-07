find_package(CxxTest)
if(CXXTEST_FOUND)
    include_directories(${CXXTEST_INCLUDE_DIR})
    include_directories(${Boost_INCLUDE_DIRS})
    include_directories(${CMAKE_BINARY_DIR})
    include_directories(${ANTLR2_INCLUDE_DIRS})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    enable_testing()
    CXXTEST_ADD_TEST(unittest_foo foo_test.cc
                      ${CMAKE_CURRENT_SOURCE_DIR}/foo_test.h
                      ${CMAKE_CURRENT_SOURCE_DIR}/test_basic.hpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/test_re2c.hpp)
                  target_link_libraries(unittest_foo smali myantlr ${Boost_LIBRARIES}) # as needed
endif()


add_custom_command(OUTPUT SmaliLexer.cpp SmaliLexer.hpp SmaliLexerTokenTypes.hpp SmaliLexerTokenTypes.txt SmaliParser.cpp SmaliParser.hpp
    COMMAND ${ANTLR2_EXECUTABLE} -trace ${CMAKE_CURRENT_SOURCE_DIR}/smali.antlr
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/smali.antlr
)

include_directories(${ANTLR2_INCLUDE_DIRS})
add_library(smali STATIC  SmaliLexer.cpp SmaliParser.cpp)

include_directories(${CMAKE_CURRENT_BINARY_PAHT})

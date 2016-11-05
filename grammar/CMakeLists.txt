add_custom_command(OUTPUT SmaliLexer.cpp SmaliLexer.hpp SmaliLexerTokenTypes.hpp SmaliLexerTokenTypes.txt SmaliParser.cpp SmaliParser.hpp
    COMMAND runantlr ${CMAKE_CURRENT_SOURCE_DIR}/smali.antlr
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/smali.antlr
)

add_library(smali STATIC  SmaliLexer.cpp SmaliParser.cpp)


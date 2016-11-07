add_custom_command(OUTPUT SmaliLexer.cpp SmaliLexer.hpp SmaliLexerTokenTypes.hpp SmaliLexerTokenTypes.txt SmaliParser.cpp SmaliParser.hpp
    COMMAND java -cp ${CMAKE_SOURCE_DIR}/external/antlr-2.7.7/antlr.jar antlr.Tool  -trace ${CMAKE_CURRENT_SOURCE_DIR}/smali.antlr
    #COMMAND runantlr -debug -diagnostic -trace ${CMAKE_CURRENT_SOURCE_DIR}/smali.antlr
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/smali.antlr
)

add_custom_command(OUTPUT Re2cLexer.cpp 
    COMMAND re2c ${CMAKE_CURRENT_SOURCE_DIR}/Re2cLexer.re -o ${CMAKE_CURRENT_BINARY_DIR}/Re2cLexer.cpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Re2cLexer.re
)

include_directories(${ANTLR2_INCLUDE_DIRS})
add_library(smali STATIC  SmaliLexer.cpp SmaliParser.cpp Re2cLexer.cpp)

include_directories(${CMAKE_CURRENT_BINARY_PAHT})


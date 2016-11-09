add_custom_command(OUTPUT Re2cTokenTypes.txt
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/Re2cTokenTypes.txt ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Re2cTokenTypes.txt
)

add_custom_command(OUTPUT SmaliParser.cpp SmaliParser.hpp
    COMMAND java -cp ${CMAKE_SOURCE_DIR}/external/antlr-2.7.7/antlr.jar antlr.Tool  -trace ${CMAKE_CURRENT_SOURCE_DIR}/smali.antlr
    #COMMAND runantlr -debug -diagnostic -trace ${CMAKE_CURRENT_SOURCE_DIR}/smali.antlr
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/smali.antlr ${CMAKE_CURRENT_BINARY_DIR}/Re2cTokenTypes.txt
)

add_custom_command(OUTPUT Re2cLexer.cpp 
    COMMAND re2c ${CMAKE_CURRENT_SOURCE_DIR}/Re2cLexer.re -o ${CMAKE_CURRENT_BINARY_DIR}/Re2cLexer.cpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Re2cLexer.re
)

#set(smali_parser_re2c_gen_file ${CMAKE_CURRENT_BINARY_DIR}/SmaliRe2cParserAux.cpp)
#set(smali_parser_re2c_src_file ${CMAKE_CURRENT_SOURCE_DIR}/smali.re)
#add_custom_command(OUTPUT ${smali_parser_re2c_gen_file}
    #COMMAND re2c ${smali_parser_re2c_src_file} -o ${smali_parser_re2c_gen_file}
    #DEPENDS ${smali_parser_re2c_src_file}
#)

include_directories(${ANTLR2_INCLUDE_DIRS})
add_library(smali STATIC  SmaliParser.cpp Re2cLexer.cpp Re2cProcessorBase.cpp ) #${smali_parser_re2c_gen_file})

include_directories(${CMAKE_CURRENT_BINARY_PAHT})


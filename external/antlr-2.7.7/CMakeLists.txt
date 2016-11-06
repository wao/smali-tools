set(ANTLR2_SOURCES
    lib/cpp/src/ANTLRUtil.cpp
    lib/cpp/src/ASTFactory.cpp
    lib/cpp/src/ASTNULLType.cpp
    lib/cpp/src/ASTRefCount.cpp
    lib/cpp/src/BaseAST.cpp
    lib/cpp/src/BitSet.cpp
    lib/cpp/src/CharBuffer.cpp
    lib/cpp/src/CharScanner.cpp
    lib/cpp/src/CommonAST.cpp
    lib/cpp/src/CommonASTWithHiddenTokens.cpp
    lib/cpp/src/CommonHiddenStreamToken.cpp
    lib/cpp/src/CommonToken.cpp
    #    lib/cpp/src/dll.cpp
    lib/cpp/src/InputBuffer.cpp
    lib/cpp/src/LLkParser.cpp
    lib/cpp/src/MismatchedCharException.cpp
    lib/cpp/src/MismatchedTokenException.cpp
    lib/cpp/src/NoViableAltException.cpp
    lib/cpp/src/NoViableAltForCharException.cpp
    lib/cpp/src/Parser.cpp
    lib/cpp/src/RecognitionException.cpp
    lib/cpp/src/String.cpp
    lib/cpp/src/TokenBuffer.cpp
    lib/cpp/src/Token.cpp
    lib/cpp/src/TokenRefCount.cpp
    lib/cpp/src/TokenStreamBasicFilter.cpp
    lib/cpp/src/TokenStreamHiddenTokenFilter.cpp
    lib/cpp/src/TokenStreamRewriteEngine.cpp
    lib/cpp/src/TokenStreamSelector.cpp
    lib/cpp/src/TreeParser.cpp
    )

set(ANTLR2_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/lib/cpp)
set(ANTLR2_EXECUTABLE java -cp ${CMAKE_CURRENT_SOURCE_DIR}/antlr.jar antlr.Tool)

include_directories(${ANTLR2_INCLUDE_DIRS})
add_library(myantlr ${ANTLR2_SOURCES})

#set(ANTLR2_LIBARIES ${CMAKE_BINARY_DIR}/antlr/lib/libantlr.a)

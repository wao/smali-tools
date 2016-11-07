#include <cxxtest/TestSuite.h>

#include "grammar/Re2cLexer.hpp"
#include "grammar/Re2cTokenType.hpp"


class Re2cLexerBasicTestSuite : public CxxTest::TestSuite
{
public:
    void parseString(const std::string& input_str, std::function<void (Re2cLexer&)> func, int buf_len = 512){
        std::istringstream input(input_str);
        Re2cLexer lexer(input, buf_len);
        TS_ASSERT_THROWS_NOTHING( func(lexer) );
    }

    static void checkToken( antlr::TokenStream& lexer, int token_type, const std::string& literal ){
        antlr::RefToken token;
        TS_ASSERT_THROWS_NOTHING( token = lexer.nextToken() );
        TS_ASSERT_EQUALS( token->getType(), token_type );
        TS_ASSERT_EQUALS( token->getText(), literal );
    }

    void testBasic(){
        parseString( ".method", [](Re2cLexer& lexer){
                checkToken( lexer, DIR_METHOD, ".method" );
        });

        parseString( ".method ma(Ljava/lang/util/anything/String;)V", [](Re2cLexer& lexer){
                checkToken( lexer, DIR_METHOD, ".method" );
                checkToken( lexer, ID, "ma" );
                checkToken( lexer, LEFT_PAREN, "(" );
                checkToken( lexer, CLASSNAME, "Ljava/lang/util/anything/String;" );
                checkToken( lexer, RIGHT_PAREN, ")" );
                checkToken( lexer, ID, "V" );
        });

        parseString( ".method ma(Ljava/lang/util/anything/String;)V", [](Re2cLexer& lexer){
                checkToken( lexer, DIR_METHOD, ".method" );
                checkToken( lexer, ID, "ma" );
                checkToken( lexer, LEFT_PAREN, "(" );
                checkToken( lexer, CLASSNAME, "Ljava/lang/util/anything/String;" );
                checkToken( lexer, RIGHT_PAREN, ")" );
                checkToken( lexer, ID, "V" );
        }, 35);
        
        // Too small buf to hold literal, general meet on comments, should fix it! 
        // Return a invalid status or strip comment, not to send to lexer, both need maybe.
        /*
        parseString( ".method ma(Ljava/lang/util/anything/String;)V", [](Re2cLexer& lexer){
                checkToken( lexer, DIR_METHOD, ".method" );
                checkToken( lexer, ID, "ma" );
                checkToken( lexer, LEFT_PAREN, "(" );
                checkToken( lexer, CLASSNAME, "Ljava/lang/util/anything/String;" );
                checkToken( lexer, RIGHT_PAREN, ")" );
                checkToken( lexer, ID, "V" );
        }, 12);
        */
    }
};

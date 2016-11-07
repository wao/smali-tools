#include <assert.h>
#include <cstring>
#include <exception>
#include <memory>
#include "grammar/Re2cLexer.hpp"
#include "grammar/Re2cTokenType.hpp"
#include "antlr/CommonToken.hpp"

#define	YYCTYPE		    char
#define YYCURSOR        cursor
#define	YYMARKER		yymark
#define YYLIMIT         yylimit
#define YYFILL(n) {\
    if( fillData( literal_first - buf_, cursor - buf_, n ) ){ \
        int offset = literal_first - buf_; \
        literal_first = buf_; \
        cursor -= offset; \
        yymark -= offset; \
        yylimit = buf_ + data_end_; \
    } \
}

#define RETURN(token_type) {\
    std::unique_ptr<antlr::CommonToken> token_ptr(new antlr::CommonToken(token_type, std::string(literal_first, cursor)));\
    return antlr::RefToken(token_ptr.release());\
}
    

antlr::RefToken Re2cLexer::nextToken()
{
    char ch;
    char *cursor = buf_ + data_start_;
    char *yymark;
    char *yylimit = buf_ + data_end_;

    for(;;) {
        char * literal_first = cursor;

        /*!re2c
      re2c:indent:top = 1;
      re2c:indent:string = "    ";

      ANY = [\000-\377];
      SPACE = [ \t];
      DIGIT = [0-9];
      ALPHA = [a-zA-Z];
      ID = ( "_" | ALPHA)( "_"|ALPHA|DIGIT|"$")*;

      ".method"   
            { RETURN(DIR_METHOD); }
      ".end" SPACE+ "method" 
            { RETURN(END_METHOD); }
      ".class" { RETURN(DIR_CLASS); }
      ".local" { RETURN(DIR_LOCAL); }
      ".locals" { RETURN(DIR_LOCALS); }
      ".source" { RETURN(DIR_SOURCE); }
      ".annotation" { RETURN(DIR_ANNOTATION); }
      ".end"  SPACE+ "annotation" { RETURN(END_ANNOTATION); }
      ".super" { RETURN(DIR_SUPER); }
      "L" ID ( "/" ID )* ";" { RETURN(CLASSNAME); }
       ID { RETURN(ID); }
      

      "\n"        
          { 
              if( eof() ){
                  //TODO should handle it. is 0 a good one???
                RETURN(0);
              }
              nextline(); 
              continue;
          }
      
       *
          {
                reportError();
          }
    */
    }
}

void Re2cLexer::readData(int offset, int need_chars){
    assert( offset >= 0 );
    assert( offset < BUFLEN );
    assert( offset == data_end_ ); 
    assert( offset + need_chars <= BUFLEN );

    input_stream_.read( (char*)&buf_+offset, BUFLEN - offset );
    data_end_ += input_stream_.gcount();

    if( input_stream_.gcount() < need_chars ){
        if( input_stream_.eof() ){
            for(int i = input_stream_.gcount(); i < need_chars; ++i){
                buf_[data_end_ + i] = '\n';
            }
            data_end_ += need_chars - input_stream_.gcount();

        }else{
            std::cerr << "Stream error in readData";
            throw std::runtime_error("Stream error!");
        }
    }

    assert( data_end_ <= BUFLEN );
    assert( data_end_ > 0 );
    assert( data_end_ - offset >= need_chars );

}

bool Re2cLexer::eof(){
    return input_stream_.eof();
}

bool Re2cLexer::fillData(int first_char_index_should_keep, int index_to_put_new_data, int need_chars ){
    bool retval = false;
    assert( index_to_put_new_data == data_end_ ); //it's my assumptation, otherwise, following code need to tune
    if( need_chars > (BUFLEN - data_end_ ) ){
        retval = true;

        //check if we can full fill need_chars after move
        if( need_chars > (BUFLEN - ( data_end_ - first_char_index_should_keep ))){
            assert(false); //FIXME should handle this
        }

        std::memmove( buf_, buf_+first_char_index_should_keep, data_end_ - first_char_index_should_keep );
                
        data_end_ = data_end_ - first_char_index_should_keep;
    }

    readData(data_end_,need_chars);

    return retval;
}

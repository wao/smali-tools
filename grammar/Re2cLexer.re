#include <assert.h>
#include <cstring>
#include <exception>
#include <memory>
#include "grammar/Re2cLexer.hpp"
#include "grammar/Re2cTokenType.hpp"
#include "antlr/CommonToken.hpp"

#define reportError() reportError( __FILE__, __LINE__, std::string(literal_first, cursor + 1), cursor )
#define	YYCTYPE		    char
#define YYCURSOR        cursor
#define	YYMARKER		yymark
#define YYLIMIT         yylimit
#define YYFILL(n) {\
    if( fillData( literal_first - buf_, cursor - buf_, n ) ){ \
        int offset = literal_first - buf_; \
        literal_first = buf_; \
        cursor -= offset; \
        col_ptr_ -= offset; \
        yymark -= offset; \
        yylimit = buf_ + data_end_; \
    } \
}

#define RETURN(token_type) {\
    std::unique_ptr<antlr::CommonToken> token_ptr(new antlr::CommonToken(token_type, std::string(literal_first, cursor)));\
    data_start_ = cursor - buf_; \
    std::cerr << "Return token:" << token_type << std::endl; \
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
        col_no_ += cursor - col_ptr_;
        col_ptr_ = cursor;

        /*!re2c
      re2c:indent:top = 1;
      re2c:indent:string = "    ";

      ANY = [\000-\377];
      SPACE = [ \t];
      DIGIT = [0-9];
      ALPHA = [a-zA-Z];
      ID = ( "_" | ALPHA)( "_"|ALPHA|DIGIT|"$")*;
      SEMICOLON = ";";
      COLON = ":";
      SLASH = "/";

      ".method"   
            { RETURN(DIR_METHOD); }
      ".end" SPACE+ "method" 
            { RETURN(END_METHOD); }
      ".class" { RETURN(DIR_CLASS); }
      ".local" { RETURN(DIR_LOCAL); }
      ".locals" { RETURN(DIR_LOCALS); }
      ".source" { RETURN(DIR_SOURCE); }
      ".field" { RETURN(DIR_FIELD); }
      ".annotation" { RETURN(DIR_ANNOTATION); }
      ".end"  SPACE+ "annotation" { RETURN(END_ANNOTATION); }
      ".super" { RETURN(DIR_SUPER); }
       "public" { RETURN(PUBLIC); }
       "private" { RETURN(PRIVATE);}

      "L" ID ( SLASH ID )* SEMICOLON { RETURN(CLASSNAME); }
       ID { RETURN(ID); }

       "(" { RETURN(LEFT_PAREN); }
       ")" { RETURN(RIGHT_PAREN); }
       "{" { RETURN(LEFT_BRACE); }
       "}" { RETURN(RIGHT_BRACE); }
       "=" { RETURN(ASSIGN); }
       SLASH { RETURN(SLASH);}
       SEMICOLON { RETURN(SEMICOLON); }
       COLON { RETURN(COLON); }

       "\"" [^"]* "\"" { RETURN(STRING); }

       


      "\n"        
          { 
              if( eof(cursor) ){
                  //TODO should handle it. is 0 a good one???
                RETURN(-1);
              }
              nextline(cursor); 
              continue;
          }

      SPACE+ 
          {
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
    std::cerr << "readData:" << offset << "," << need_chars << std::endl;
    assert( offset >= 0 );
    assert( offset < buf_len_ );
    assert( offset == data_end_ ); 
    assert( offset + need_chars <= buf_len_ );

    input_stream_.read( buf_+offset, buf_len_ - offset );
    data_end_ += input_stream_.gcount();

    if( input_stream_.gcount() < need_chars ){
        if( input_stream_.eof() ){
            is_stream_eof_ = true;
            end_pos_ = buf_ + data_end_;
            for(int i = input_stream_.gcount(); i < need_chars; ++i){
                std::cerr << "fillData: append fake endline:" <<  need_chars << std::endl;
                buf_[data_end_ + i] = '\n';
            }
            data_end_ += need_chars - input_stream_.gcount();

        }else{
            std::cerr << "Stream error in readData";
            throw std::runtime_error("Stream error!");
        }
    }

    assert( data_end_ <= buf_len_ );
    assert( data_end_ > 0 );
    assert( data_end_ - offset >= need_chars );

}

bool Re2cLexer::eof(char * cursor){
    if( is_stream_eof_ ){
        if( cursor >= end_pos_ ){
            return true;
        }
    }
    return false;
}

bool Re2cLexer::fillData(int first_char_index_should_keep, int index_to_put_new_data, int need_chars ){
    bool retval = false;

    std::cerr << "fillData:" << first_char_index_should_keep << "," << index_to_put_new_data << "," << need_chars << std::endl;

    assert( index_to_put_new_data <= data_end_ );
    //index_to_put_new_data may not reach data_end_

    if( ( index_to_put_new_data + need_chars ) <= data_end_ ){
        //already meet requirement, should happend
        assert(false);
    }

    //adjust if data_end_ != index_to_put_new_data
    need_chars -= data_end_ - index_to_put_new_data;
    assert( need_chars > 0 );
    index_to_put_new_data = data_end_;

    if( need_chars > (buf_len_ - data_end_ ) ){
        retval = true;

        //check if we can full fill need_chars after move
        if( need_chars > (buf_len_ - ( data_end_ - first_char_index_should_keep ))){
            assert(false); //FIXME should handle this
        }

        std::cerr << "moveData:" << data_end_ - first_char_index_should_keep << std::endl;
        std::memmove( buf_, buf_+first_char_index_should_keep, data_end_ - first_char_index_should_keep );
                
        data_end_ = data_end_ - first_char_index_should_keep;
    }

    readData(data_end_,need_chars);

    return retval;
}

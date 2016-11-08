#ifndef __RE2CLEXER_HPP
#define __RE2CLEXER_HPP

#include "antlr/TokenStream.hpp"
#include <iostream>
#include <memory>

class Re2cLexer : public antlr::TokenStream{
public:
    static constexpr int BUFLEN = 1024 * 16;
    Re2cLexer(std::istream& input_stream, unsigned int buflen = BUFLEN) : input_stream_(input_stream), buf_mgr_( new char[buflen] ), buf_len_( buflen )
    {
        buf_ = buf_mgr_.get();
    }

	virtual antlr::RefToken nextToken() override;

    enum class Mode { None, Register, TypeId };

    void setMode( Mode new_mode ){
        mode_ = new_mode;
    }

private:
    std::istream& input_stream_;
    std::unique_ptr<char[]> buf_mgr_;
    int buf_len_;
    char * buf_;
    int data_end_ = 0;
    int data_start_ = 0; 
    int line_no_ = 1;
    int col_no_ = 1;
    char * col_ptr_;
    bool is_stream_eof_ = false;
    char * end_pos_ = 0;

    Mode mode_;


    //read data to 
    void readData(int offset, int need_chars);

    /*
     @retval true: need to adjust pointer since buf has relocation
    */
    bool fillData(int first_char_index_should_keep, int index_to_put_new_data, int need_chars );

    bool eof(char * cursor);

    void reportError( const char * filename, int lineno, const std::string& literal, char * cursor ){
        //FIXME add log here
        std::cerr << "Error here: " << filename << ":" << lineno << std::endl;
        std::cerr << "Meet [" << literal << "]" << " at line " << line_no_ << " col " << col_no_ + ( cursor - col_ptr_ ) <<   std::endl;
        throw std::runtime_error("Re2xLexer error!");
    }

    void clearMode(){
        mode_ = Mode::None;
    }

    void nextline(char * cursor){
        line_no_ ++;
        col_no_ = 1;
        col_ptr_ = cursor;
    }
};

#endif /*__RE2CLEXER_HPP*/

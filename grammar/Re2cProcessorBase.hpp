#ifndef __RE2CPROCESSORBASE_HPP
#define __RE2CPROCESSORBASE_HPP

#include <iostream>
#include <memory>

class Re2cProcessorBase {
public:
    static constexpr int BUFLEN = 1024 * 16;

    Re2cProcessorBase(std::istream& input_stream, unsigned int buflen = BUFLEN) : input_stream_(input_stream), buf_mgr_( new char[buflen] ), buf_len_( buflen )
    {
        buf_ = buf_mgr_.get();
    }

    typedef char CharType;

protected:
    std::istream& input_stream_;
    std::unique_ptr<CharType[]> buf_mgr_;
    int buf_len_;
    CharType * buf_;
    int data_end_ = 0;
    int data_start_ = 0; 
    int line_no_ = 1;
    int col_no_ = 1;
    CharType * col_ptr_;
    bool is_stream_eof_ = false;
    CharType * end_pos_ = 0;
    //read data to 
    void readData(int offset, int need_chars);

    /*
     @retval true: need to adjust pointer since buf has relocation
    */
    bool fillData(int first_char_index_should_keep, int index_to_put_new_data, int need_chars );

    bool eof(CharType * cursor);

    virtual void reportError( const char * filename, int lineno, const std::string& literal, CharType * cursor );

    virtual void nextline(CharType * cursor);
};

#endif /*__RE2CPROCESSORBASE_HPP*/

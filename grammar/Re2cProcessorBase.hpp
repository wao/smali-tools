#ifndef __RE2CPROCESSORBASE_HPP
#define __RE2CPROCESSORBASE_HPP

#include <iostream>
#include <memory>
#include <assert.h>

class Re2cProcessorBase {
public:
    static constexpr int BUFLEN = 1024 * 16;

    Re2cProcessorBase(std::istream& input_stream, unsigned int buflen = BUFLEN) : input_stream_(input_stream), buf_mgr_( new char[buflen] ), buf_len_( buflen )
    {
        buf_ = buf_mgr_.get();
    }

    typedef char CharType;

private:
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
    CharType * literal_first_ = 0;
    //read data to 
    void readData(int offset, int need_chars);

protected:
    inline int fillData( int need_chars, CharType*& cursor, CharType*& limit, CharType*& mark ){
         int offset = fillData(need_chars, cursor, limit );
         if( offset > 0 ) {
             mark -= offset;
         }

         return offset;
    }

    inline int fillData( int need_chars, CharType*& cursor, CharType*& limit ){
        int offset = doFillData( literal_first_ - buf_, cursor - buf_, need_chars );
        if( offset > 0 ){
            assert( offset < buf_len_ );
            literal_first_ = buf_; 
            cursor -= offset; 
            col_ptr_ -= offset; 
            limit = buf_ + data_end_; 
        }

        return offset;
    }

    /*
     @retval true: need to adjust pointer since buf has relocation
    */
    int doFillData(int first_char_index_should_keep, int index_to_put_new_data, int need_chars );

    inline void loadBuf( CharType*& cursor, CharType*& limit ){
        cursor = buf_ + data_start_;
        limit = buf_ + data_end_;
    }

    inline void startNewMatch(CharType * cursor ){
        literal_first_ = cursor;
        col_no_ += cursor - col_ptr_;
        col_ptr_ = cursor;

    }

    inline void finishMatch(CharType * cursor ){
        data_start_ = cursor - buf_;
    }

    inline CharType * getLiteralFirst() const{
        return literal_first_;
    }


    bool eof(CharType * cursor);

    virtual void reportError( const char * filename, int lineno, const std::string& literal, CharType * cursor );

    virtual void nextline(CharType * cursor);
};

#endif /*__RE2CPROCESSORBASE_HPP*/

#include <assert.h>
#include <cstring>
#include <exception>
#include <memory>
#include "grammar/Re2cProcessorBase.hpp"

void Re2cProcessorBase::readData(int offset, int need_chars){
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

bool Re2cProcessorBase::eof(CharType * cursor){
    if( is_stream_eof_ ){
        if( cursor >= end_pos_ ){
            return true;
        }
    }
    return false;
}

int Re2cProcessorBase::doFillData(int first_char_index_should_keep, int index_to_put_new_data, int need_chars ){
    int retval = 0;

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

        retval = first_char_index_should_keep;
        std::cerr << "moveData:" << data_end_ - first_char_index_should_keep << std::endl;
        std::memmove( buf_, buf_+first_char_index_should_keep, data_end_ - first_char_index_should_keep );
                
        data_end_ = data_end_ - first_char_index_should_keep;
    }

    readData(data_end_,need_chars);

    return retval;
}

void Re2cProcessorBase::reportError( const char * filename, int lineno, const std::string& literal, CharType * cursor ){
    //FIXME add log here
    std::cerr << "Error here: " << filename << ":" << lineno << std::endl;
    std::cerr << "Meet [" << literal << "]" << " at line " << line_no_ << " col " << col_no_ + ( cursor - col_ptr_ ) <<   std::endl;
    throw std::runtime_error("Re2xLexer error!");
}

void Re2cProcessorBase::nextline(CharType * cursor){
    line_no_ ++;
    col_no_ = 1;
    col_ptr_ = cursor;
}

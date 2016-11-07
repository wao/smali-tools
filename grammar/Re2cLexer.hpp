#include "antlr/TokenStream.hpp"
#include <iostream>
#include <memory>

class Buffer
{
};

class Re2cLexer : public antlr::TokenStream{
public:
    static constexpr int BUFLEN = 1024 * 16;
    Re2cLexer(std::istream& input_stream, unsigned int buflen = BUFLEN) : input_stream_(input_stream), buf_mgr_( new char[buflen] ), buf_len_( buflen )
    {
        buf_ = buf_mgr_.get();
    }

	virtual antlr::RefToken nextToken() override;

private:
    std::istream& input_stream_;
    std::unique_ptr<char[]> buf_mgr_;
    int buf_len_;
    char * buf_;
    int data_end_ = 0;
    int data_start_ = 0; 


    //read data to 
    void readData(int offset, int need_chars);

    /*
     @retval true: need to adjust pointer since buf has relocation
    */
    bool fillData(int first_char_index_should_keep, int index_to_put_new_data, int need_chars );

    bool eof();

    void reportError( const char * filename, int lineno, const std::string& literal ){
        //FIXME add log here
        std::cerr << "Error here: " << filename << ":" << lineno << std::endl;
        std::cerr << "Meet [" << literal << "]" << std::endl;
        assert(false);
    }

    void nextline(){
    }
};

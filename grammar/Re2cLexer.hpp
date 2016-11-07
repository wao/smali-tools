#include "antlr/TokenStream.hpp"
#include <iostream>

class Buffer
{
};

class Re2cLexer : public antlr::TokenStream{
public:
    Re2cLexer(std::istream& input_stream) : input_stream_(input_stream){}

	virtual antlr::RefToken nextToken() override;

private:
    static constexpr int BUFLEN = 512;
    std::istream& input_stream_;
    char buf_[BUFLEN];
    int data_end_ = 0;
    int data_start_ = 0; 


    //read data to 
    void readData(int offset, int need_chars);

    /*
     @retval true: need to adjust pointer since buf has relocation
    */
    bool fillData(int first_char_index_should_keep, int index_to_put_new_data, int need_chars );

    bool eof();

    void reportError(){
        //FIXME add log here
        std::cerr << "Error here";
        assert(false);
    }

    void nextline(){
    }
};

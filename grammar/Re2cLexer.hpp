#ifndef __RE2CLEXER_HPP
#define __RE2CLEXER_HPP

#include "antlr/TokenStream.hpp"
#include <iostream>
#include <memory>

#include "grammar/Re2cProcessorBase.hpp"

enum class LexerMode { None, fieldName, returnTypeId, parameterTypeIds };

class Re2cLexer : public antlr::TokenStream, public Re2cProcessorBase{
public:
    using Re2cProcessorBase::Re2cProcessorBase;

	virtual antlr::RefToken nextToken() override;


    void setMode( LexerMode new_mode ){
        mode_ = new_mode;
    }

private:
    LexerMode mode_;


    void clearMode(){
        mode_ = LexerMode::None;
    }
};

#endif /*__RE2CLEXER_HPP*/

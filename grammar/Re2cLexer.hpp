#ifndef __RE2CLEXER_HPP
#define __RE2CLEXER_HPP

#include "antlr/TokenStream.hpp"
#include <iostream>
#include <memory>

#include "grammar/Re2cProcessorBase.hpp"

class Re2cLexer : public antlr::TokenStream, public Re2cProcessorBase{
public:
    using Re2cProcessorBase::Re2cProcessorBase;

	virtual antlr::RefToken nextToken() override;

    enum class Mode { None, Register, TypeId };

    void setMode( Mode new_mode ){
        mode_ = new_mode;
    }

private:
    Mode mode_;


    void clearMode(){
        mode_ = Mode::None;
    }
};

#endif /*__RE2CLEXER_HPP*/

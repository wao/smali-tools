#ifndef __SMALIRE2CPARSER_HPP
#define __SMALIRE2CPARSER_HPP

#include <iostream>
#include <memory>

#include "grammar/Re2cProcessorBase.hpp"

class SmaliRe2cParser : public Re2cProcessorBase{
public:
    using Re2cProcessorBase::Re2cProcessorBase;

    void parse();
private:
    void classDecl();
    void methodDecl();
    void annotationDecl();
    void sourceDecl();
    void superDecl();
    void fieldDecl();
};

#endif /*__SMALIRE2CPARSER_HPP*/

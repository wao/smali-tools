#include <cxxtest/TestSuite.h>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include "grammar/SmaliLexer.hpp"
#include "grammar/SmaliParser.hpp"

namespace fs = boost::filesystem;

class ParserBasicTestSuite : public CxxTest::TestSuite
{
public:
   void testFile( void )
   {
       const std::string source_file_path(__FILE__);
       auto smali_file = fs::canonical(fs::path(source_file_path.begin(), source_file_path.end()).parent_path().append( "../res/smali/SnsUserUI.smali" ));
       fs::ifstream input_file(smali_file);
   }

private: 
   static void parseString(const std::string& input_str,const std::function<void (SmaliParser&)>& f){
       std::istringstream input(input_str);
       SmaliLexer lexer(input);
       SmaliParser parser(lexer);
       f(parser);
   }

public:
   void testParser(){
       parseString(std::string(".class public Lcom/tencent/mm/plugin/sns/ui/SnsUserUI;"),[](SmaliParser& parser){
               try{
               parser.classDecl();
               }catch(std::exception e){
               std::cout << e.what();
               }
               });

   }
};

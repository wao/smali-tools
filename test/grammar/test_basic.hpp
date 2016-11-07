#include <cxxtest/TestSuite.h>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include "grammar/Re2cLexer.hpp"
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
       Re2cLexer lexer(input);
       SmaliParser parser(lexer);
       try{
           f(parser);
       }catch(std::exception const& e){
           std::cout << e.what();
           throw e;
       }
   }

public:
   void testParser(){
       parseString(".class public Lcom/tencent/mm/plugin/sns/ui/SnsUserUI;",[](SmaliParser& parser){
               TS_ASSERT_THROWS_NOTHING(parser.classDecl());
       });
       parseString(".super Lcom/tencent/mm/plugin/sns/ui/SnsUserUI;",[](SmaliParser& parser){
               TS_ASSERT_THROWS_NOTHING(parser.superDecl());
               });
       parseString(".source \"SourceFile\"",[](SmaliParser& parser){
               TS_ASSERT_THROWS_NOTHING(parser.sourceDecl());
               });
       parseString(".source \"SourceFile\"",[](SmaliParser& parser){
               TS_ASSERT_THROWS_NOTHING(parser.sourceDecl());
               });
       parseString(".field private gdM:Lcom/tencent/mm/plugin/sns/ui/ab;",[](SmaliParser& parser){
               TS_ASSERT_THROWS_NOTHING(parser.fieldDecl());
               });

       parseString(R"(.annotation system Ldalvik/annotation/MemberClasses;
    value = {
        Lcom/tencent/mm/plugin/sns/ui/SnsUserUI$a;
    }
.end annotation)", [](SmaliParser& parser){
               TS_ASSERT_THROWS_NOTHING(parser.annotationDecl());
               });
               

   }
};

#include "grammar/SmaliRe2cParser.hpp"

#define reportError() reportError( __FILE__, __LINE__, std::string(getLiteralFirst(), cursor + 1), cursor )
#define	YYCTYPE		    CharType
#define YYCURSOR        cursor
#define	YYMARKER		yymark
#define YYLIMIT         yylimit
#define YYFILL(n) {\
    int offset = fillData( n, cursor, yylimit, yymark ); \
    if( offset > 0 ){ \
    } \
}

#define CALL(name)  {\
    finishMatch(cursor); \
    name();\
    continue;\
}

#define BEGIN_RE2C_FOR() \
    CharType ch;\
    CharType *cursor;\
    CharType *yymark;\
    CharType *yylimit;\
\
   loadBuf( cursor, yylimit );\
\
    for(;;) {\
        startNewMatch(cursor);



#define END_RE2C_FOR()

    }
}

void SmaliRe2cParser::parse(){
BEGIN_RE2C_FOR()
        /*!re2c
        re2c:indent:top = 1;
        re2c:indent:string = "    ";

        SPACE = [ \t];

        ".class" { CALL(classDecl); }
        ".method" { CALL(methodDecl); }
        ".annotation" { CALL(annotationDecl); }
        ".source" { CALL(sourceDecl); }
        ".field" { CALL(fieldDecl); }
        ".super" { CALL(superDecl); }

          "\n"        
          { 
              if( eof(cursor) ){
                //TODO should handle it. is 0 a good one???
                //RETURN(-1);
                return;
              }
              nextline(cursor); 
              continue;
          }


        SPACE+ { continue; }
        * { reportError(); }
        */
END_RE2C_FOR()
}


void SmaliRe2cParser::classDecl(){
    skipSpace();
    visualDecl();
    skipSpace();
    classNameDecl();
    skipSpaceToLineEnd();
}

void SmaliRe2cParser::skipSpace(){
    BEGIN_RE2C_FOR()
        /*!re2c
        re2c:indent:top = 1;
        re2c:indent:string = "    ";

        SPACE = [ \t];

        SPACE+ { continue; }

        * { 
            finishMatch(); 
            return;
        }
         */
    END_RE2C_FOR()
}

void SmaliRe2cParser::skipSpace(){
}

void SmaliRe2cParser::visualDecl(){
    BEGIN_RE2C_FOR()
        /*!re2c
        re2c:indent:top = 1;
        re2c:indent:string = "    ";

        "private" { return; }
        "public" { return; }
        * { reportError(); }
        */
    END_RE2C_FOR()
}

void SmaliRe2cParser::classNameDecl(){
    BEGIN_RE2C_FOR()
        /*!re2c
        re2c:indent:top = 1;
        re2c:indent:string = "    ";

        DIGIT = [0-9];
        ALPHA = [a-zA-Z];
        ID = ( "_" | ALPHA)( "_"|ALPHA|DIGIT|"$")*;
        
        "L" ID ( "/" ID )* ";" { finishMatch(); return; }

        * { reportError(); }
        */
    END_RE2C_FOR()
}

void SmaliRe2cParser::methodDecl(){
}

void SmaliRe2cParser::annotationDecl(){
}

void SmaliRe2cParser::sourceDecl(){
}

void SmaliRe2cParser::fieldDecl(){
}

void SmaliRe2cParser::superDecl(){
}

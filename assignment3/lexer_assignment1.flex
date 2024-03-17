%top{
    #include "parser.tab.hh"
    #define YY_DECL yy::parser::symbol_type yylex()
    #include "Node.h"
    int lexical_errors = 0;
}
%option yylineno noyywrap nounput batch noinput stack 

DIGIT           [0-9]
IDENTIFIER      [a-zA-Z_][a-zA-Z0-9_]*
INTEGER_LITERAL {DIGIT}+
WS              [ \t\n\r]+

%%

"//"[^\n]*              {}

"public" {if(USE_LEX_ONLY) {printf("PUBLIC ");} else {return yy::parser::make_PUBLIC(std::to_string(yylineno));}}
"static" {if(USE_LEX_ONLY) {printf("STATIC ");} else {return yy::parser::make_STATIC(std::to_string(yylineno));}}
"class" {if(USE_LEX_ONLY) {printf("CLASS ");} else {return yy::parser::make_CLASS(std::to_string(yylineno));}}
"int" {if(USE_LEX_ONLY) {printf("TYPE_INT ");} else {return yy::parser::make_TYPE_INT(std::to_string(yylineno));}}
"boolean" {if(USE_LEX_ONLY) {printf("TYPE_BOOLEAN ");} else {return yy::parser::make_TYPE_BOOLEAN(std::to_string(yylineno));}}
"void" {if(USE_LEX_ONLY) {printf("VOID ");} else {return yy::parser::make_VOID(std::to_string(yylineno));}}
"String" {if(USE_LEX_ONLY) {printf("STRING ");} else {return yy::parser::make_STRING(std::to_string(yylineno));}}
"main" {if(USE_LEX_ONLY) {printf("MAIN ");} else {return yy::parser::make_MAIN(std::to_string(yylineno));}}
"if" {if(USE_LEX_ONLY) {printf("IF ");} else {return yy::parser::make_IF(std::to_string(yylineno));}}
"else" {if(USE_LEX_ONLY) {printf("ELSE ");} else {return yy::parser::make_ELSE(std::to_string(yylineno));}}
"while" {if(USE_LEX_ONLY) {printf("WHILE ");} else {return yy::parser::make_WHILE(std::to_string(yylineno));}}
"System.out.println" {if(USE_LEX_ONLY) {printf("PRINT ");} else {return yy::parser::make_PRINT(std::to_string(yylineno));}}
"return" {if(USE_LEX_ONLY) {printf("RETURN ");} else {return yy::parser::make_RETURN(std::to_string(yylineno));}}
"true" {if(USE_LEX_ONLY) {printf("TRUE ");} else {return yy::parser::make_TRUE(std::to_string(yylineno));}}
"false" {if(USE_LEX_ONLY) {printf("FALSE ");} else {return yy::parser::make_FALSE(std::to_string(yylineno));}}
"this" {if(USE_LEX_ONLY) {printf("THIS ");} else {return yy::parser::make_THIS(std::to_string(yylineno));}}
"new" {if(USE_LEX_ONLY) {printf("NEW ");} else {return yy::parser::make_NEW(std::to_string(yylineno));}}
"length" {if(USE_LEX_ONLY) {printf("LENGTH ");} else {return yy::parser::make_LENGTH(std::to_string(yylineno));}}
"!" {if(USE_LEX_ONLY) {printf("NOT ");} else {return yy::parser::make_NOT(std::to_string(yylineno));}}
"{" {if(USE_LEX_ONLY) {printf("OPEN_BRACE ");} else {return yy::parser::make_OPEN_BRACE(std::to_string(yylineno));}}
"}" {if(USE_LEX_ONLY) {printf("CLOSE_BRACE ");} else {return yy::parser::make_CLOSE_BRACE(std::to_string(yylineno));}}
"(" {if(USE_LEX_ONLY) {printf("OPEN_PAREN ");} else {return yy::parser::make_OPEN_PAREN(std::to_string(yylineno));}}
")" {if(USE_LEX_ONLY) {printf("CLOSE_PAREN ");} else {return yy::parser::make_CLOSE_PAREN(std::to_string(yylineno));}}
";" {if(USE_LEX_ONLY) {printf("SEMICOLON ");} else {return yy::parser::make_SEMICOLON(std::to_string(yylineno));}}
"," {if(USE_LEX_ONLY) {printf("COMMA ");} else {return yy::parser::make_COMMA(std::to_string(yylineno));}}
"." {if(USE_LEX_ONLY) {printf("DOT ");} else {return yy::parser::make_DOT(std::to_string(yylineno));}}
"[" {if(USE_LEX_ONLY) {printf("OPEN_BRACKET ");} else {return yy::parser::make_OPEN_BRACKET(std::to_string(yylineno));}}
"]" {if(USE_LEX_ONLY) {printf("CLOSE_BRACKET ");} else {return yy::parser::make_CLOSE_BRACKET(std::to_string(yylineno));}}
"+" {if(USE_LEX_ONLY) {printf("PLUS ");} else {return yy::parser::make_PLUS(std::to_string(yylineno));}}
"-" {if(USE_LEX_ONLY) {printf("MINUS ");} else {return yy::parser::make_MINUS(std::to_string(yylineno));}}
"*" {if(USE_LEX_ONLY) {printf("MULTIPLY ");} else {return yy::parser::make_MULTIPLY(std::to_string(yylineno));}}
"/" {if(USE_LEX_ONLY) {printf("DIVIDE ");} else {return yy::parser::make_DIVIDE(std::to_string(yylineno));}}
"&&" {if(USE_LEX_ONLY) {printf("AND ");} else {return yy::parser::make_AND(std::to_string(yylineno));}}
"||" {if(USE_LEX_ONLY) {printf("OR ");} else {return yy::parser::make_OR(std::to_string(yylineno));}}
"<" {if(USE_LEX_ONLY) {printf("LESS_THAN ");} else {return yy::parser::make_LESS_THAN(std::to_string(yylineno));}}
">" {if(USE_LEX_ONLY) {printf("GREATER_THAN ");} else {return yy::parser::make_GREATER_THAN(std::to_string(yylineno));}}
"==" {if(USE_LEX_ONLY) {printf("EQUAL ");} else {return yy::parser::make_EQUAL(std::to_string(yylineno));}}
"=" {if(USE_LEX_ONLY) {printf("ASSIGN ");} else {return yy::parser::make_ASSIGN(std::to_string(yylineno));}}

{IDENTIFIER} {if(USE_LEX_ONLY) {printf("IDENTIFIER ");} else {return yy::parser::make_IDENTIFIER(yytext);}}
{INTEGER_LITERAL} {if(USE_LEX_ONLY) {printf("INTEGER_LITERAL ");} else {return yy::parser::make_INTEGER_LITERAL(yytext);}}
{WS}             {if(USE_LEX_ONLY) {printf("WS ");}}

.                       { if(!lexical_errors) fprintf(stderr, "Lexical errors found! See the logs below: \n"); fprintf(stderr,"\t@error at line %d. Character %s is not recognized\n", yylineno, yytext); lexical_errors = 1;}
<<EOF>>                  {return yy::parser::make_END();}

%%
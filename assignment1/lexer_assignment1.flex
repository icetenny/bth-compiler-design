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

"public" {if(USE_LEX_ONLY) {printf("PUBLIC ");} else {return yy::parser::make_PUBLIC(yytext);}}
"static" {if(USE_LEX_ONLY) {printf("STATIC ");} else {return yy::parser::make_STATIC(yytext);}}
"class" {if(USE_LEX_ONLY) {printf("CLASS ");} else {return yy::parser::make_CLASS(yytext);}}
"int" {if(USE_LEX_ONLY) {printf("TYPE_INT ");} else {return yy::parser::make_TYPE_INT(yytext);}}
"boolean" {if(USE_LEX_ONLY) {printf("TYPE_BOOLEAN ");} else {return yy::parser::make_TYPE_BOOLEAN(yytext);}}
"void" {if(USE_LEX_ONLY) {printf("VOID ");} else {return yy::parser::make_VOID(yytext);}}
"String" {if(USE_LEX_ONLY) {printf("STRING ");} else {return yy::parser::make_STRING(yytext);}}
"main" {if(USE_LEX_ONLY) {printf("MAIN ");} else {return yy::parser::make_MAIN(yytext);}}
"if" {if(USE_LEX_ONLY) {printf("IF ");} else {return yy::parser::make_IF(yytext);}}
"else" {if(USE_LEX_ONLY) {printf("ELSE ");} else {return yy::parser::make_ELSE(yytext);}}
"while" {if(USE_LEX_ONLY) {printf("WHILE ");} else {return yy::parser::make_WHILE(yytext);}}
"System.out.println" {if(USE_LEX_ONLY) {printf("PRINT ");} else {return yy::parser::make_PRINT(yytext);}}
"return" {if(USE_LEX_ONLY) {printf("RETURN ");} else {return yy::parser::make_RETURN(yytext);}}
"true" {if(USE_LEX_ONLY) {printf("TRUE ");} else {return yy::parser::make_TRUE(yytext);}}
"false" {if(USE_LEX_ONLY) {printf("FALSE ");} else {return yy::parser::make_FALSE(yytext);}}
"this" {if(USE_LEX_ONLY) {printf("THIS ");} else {return yy::parser::make_THIS(yytext);}}
"new" {if(USE_LEX_ONLY) {printf("NEW ");} else {return yy::parser::make_NEW(yytext);}}
"length" {if(USE_LEX_ONLY) {printf("LENGTH ");} else {return yy::parser::make_LENGTH(yytext);}}
"!" {if(USE_LEX_ONLY) {printf("NOT ");} else {return yy::parser::make_NOT(yytext);}}
"{" {if(USE_LEX_ONLY) {printf("OPEN_BRACE ");} else {return yy::parser::make_OPEN_BRACE(yytext);}}
"}" {if(USE_LEX_ONLY) {printf("CLOSE_BRACE ");} else {return yy::parser::make_CLOSE_BRACE(yytext);}}
"(" {if(USE_LEX_ONLY) {printf("OPEN_PAREN ");} else {return yy::parser::make_OPEN_PAREN(yytext);}}
")" {if(USE_LEX_ONLY) {printf("CLOSE_PAREN ");} else {return yy::parser::make_CLOSE_PAREN(yytext);}}
";" {if(USE_LEX_ONLY) {printf("SEMICOLON ");} else {return yy::parser::make_SEMICOLON(yytext);}}
"," {if(USE_LEX_ONLY) {printf("COMMA ");} else {return yy::parser::make_COMMA(yytext);}}
"." {if(USE_LEX_ONLY) {printf("DOT ");} else {return yy::parser::make_DOT(yytext);}}
"[" {if(USE_LEX_ONLY) {printf("OPEN_BRACKET ");} else {return yy::parser::make_OPEN_BRACKET(yytext);}}
"]" {if(USE_LEX_ONLY) {printf("CLOSE_BRACKET ");} else {return yy::parser::make_CLOSE_BRACKET(yytext);}}
"+" {if(USE_LEX_ONLY) {printf("PLUS ");} else {return yy::parser::make_PLUS(yytext);}}
"-" {if(USE_LEX_ONLY) {printf("MINUS ");} else {return yy::parser::make_MINUS(yytext);}}
"*" {if(USE_LEX_ONLY) {printf("MULTIPLY ");} else {return yy::parser::make_MULTIPLY(yytext);}}
"/" {if(USE_LEX_ONLY) {printf("DIVIDE ");} else {return yy::parser::make_DIVIDE(yytext);}}
"&&" {if(USE_LEX_ONLY) {printf("AND ");} else {return yy::parser::make_AND(yytext);}}
"||" {if(USE_LEX_ONLY) {printf("OR ");} else {return yy::parser::make_OR(yytext);}}
"<" {if(USE_LEX_ONLY) {printf("LESS_THAN ");} else {return yy::parser::make_LESS_THAN(yytext);}}
">" {if(USE_LEX_ONLY) {printf("GREATER_THAN ");} else {return yy::parser::make_GREATER_THAN(yytext);}}
"==" {if(USE_LEX_ONLY) {printf("EQUAL ");} else {return yy::parser::make_EQUAL(yytext);}}
"=" {if(USE_LEX_ONLY) {printf("ASSIGN ");} else {return yy::parser::make_ASSIGN(yytext);}}

{IDENTIFIER} {if(USE_LEX_ONLY) {printf("IDENTIFIER ");} else {return yy::parser::make_IDENTIFIER(yytext);}}
{INTEGER_LITERAL} {if(USE_LEX_ONLY) {printf("INTEGER_LITERAL ");} else {return yy::parser::make_INTEGER_LITERAL(yytext);}}
{WS}             {if(USE_LEX_ONLY) {printf("WS ");}}

.                       { if(!lexical_errors) fprintf(stderr, "Lexical errors found! See the logs below: \n"); fprintf(stderr,"\t@error at line %d. Character %s is not recognized\n", yylineno, yytext); lexical_errors = 1;}
<<EOF>>                  {return yy::parser::make_END();}

%%
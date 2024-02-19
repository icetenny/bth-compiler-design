%skeleton "lalr1.cc" 
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor

%code requires{
  #include <string>
  #include "Node.h"
  #define USE_LEX_ONLY false //change this macro to true if you want to isolate the lexer from the parser.
}

%code{
  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;
  
  Node* root;
  extern int yylineno;
}

// definition of set of tokens. All tokens are of type string
%token <std::string> PUBLIC STATIC CLASS TYPE_INT TYPE_BOOLEAN VOID STRING MAIN IF ELSE WHILE PRINT RETURN LENGTH TRUE FALSE THIS NEW NOT OPEN_BRACE CLOSE_BRACE OPEN_PAREN CLOSE_PAREN SEMICOLON COMMA DOT OPEN_BRACKET CLOSE_BRACKET PLUS MINUS MULTIPLY DIVIDE AND OR LESS_THAN GREATER_THAN EQUAL ASSIGN IDENTIFIER INTEGER_LITERAL WS
%token END 0 "end of file"

//definition of operator precedence. See https://www.gnu.org/software/bison/manual/bison.html#Precedence-Decl
%left AND OR
%left LESS_THAN GREATER_THAN EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE
%left NOT

// definition of the production rules. All production rules are of type Node
%type <Node *> root main_class class_declaration var_declaration method_declaration type statement expression expression_parameter identifier identifier_parameter method_body class_body statement_group goal

%%
root:       goal END {root = $1;}
goal: main_class {$$ = new Node("GOAL", "", yylineno);
                            $$->children.push_back($1);
                            std::cerr << "Goal1" << std::endl;
                          }
            | goal class_declaration {$$ = $1;
                            $$->children.push_back($2);
                            std::cerr << "Goal2" << std::endl;
                          }
            


main_class: PUBLIC CLASS identifier OPEN_BRACE PUBLIC STATIC VOID MAIN OPEN_PAREN STRING OPEN_BRACKET CLOSE_BRACKET identifier CLOSE_PAREN OPEN_BRACE statement_group CLOSE_BRACE CLOSE_BRACE { 
                            $$ = new Node("MAIN_CLASS", "", yylineno);
                            $$->children.push_back($3);
                            Node* MAIN_CLASS_METHOD = new Node("MAIN_CLASS_METHOD", "", yylineno);
                            $$->children.push_back(MAIN_CLASS_METHOD);
                            MAIN_CLASS_METHOD->children.push_back($13);
                            MAIN_CLASS_METHOD->children.push_back($16);
                            std::cerr << "Main Class" << std::endl;
                          }

class_declaration: CLASS identifier OPEN_BRACE class_body CLOSE_BRACE { 
                            $$ = new Node("CLASS_DECLARATION", "", yylineno);
                            $$->children.push_back($2);
                            $$->children.push_back($4);
                            std::cerr << "Class Decl1" << std::endl;
                          }
                  | CLASS identifier OPEN_BRACE CLOSE_BRACE { 
                            $$ = new Node("CLASS_DECLARATION", "", yylineno);
                            $$->children.push_back($2);
                            std::cerr << "Class Decl2" << std::endl;
                          }

var_declaration: type identifier SEMICOLON { 
                            $$ = new Node("VAR_DECLARATION", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($2);
                            std::cerr << "Var Decl" << std::endl;
                          }

method_declaration: PUBLIC type identifier OPEN_PAREN identifier_parameter CLOSE_PAREN OPEN_BRACE method_body RETURN expression SEMICOLON CLOSE_BRACE {
                            $$ = new Node("METHOD_DECLARATION", "", yylineno);
                            Node* NODE_RETURN_TYPE = new Node("RETURN_TYPE", "", yylineno);
                            $$->children.push_back(NODE_RETURN_TYPE);
                            NODE_RETURN_TYPE->children.push_back($2);
                            $$->children.push_back($3);
                            $$->children.push_back($5);
                            $$->children.push_back($8);
                            Node* NODE_RETURN = new Node("RETURN", "", yylineno);
                            $$->children.push_back(NODE_RETURN);
                            NODE_RETURN->children.push_back($10);
                            std::cerr << "Method Decl1" << std::endl;
                          }
                  | PUBLIC type identifier OPEN_PAREN identifier_parameter CLOSE_PAREN OPEN_BRACE RETURN expression SEMICOLON CLOSE_BRACE {
                            $$ = new Node("METHOD_DECLARATION", "", yylineno);
                            Node* NODE_RETURN_TYPE = new Node("RETURN_TYPE", "", yylineno);
                            $$->children.push_back(NODE_RETURN_TYPE);
                            NODE_RETURN_TYPE->children.push_back($2);
                            $$->children.push_back($3);
                            $$->children.push_back($5);
                            Node* NODE_RETURN = new Node("RETURN", "", yylineno);
                            $$->children.push_back(NODE_RETURN);
                            NODE_RETURN->children.push_back($9);
                            std::cerr << "Method Decl2" << std::endl;
                          }
                  | PUBLIC type identifier OPEN_PAREN CLOSE_PAREN OPEN_BRACE method_body RETURN expression SEMICOLON CLOSE_BRACE {
                            $$ = new Node("METHOD_DECLARATION", "", yylineno);
                            Node* NODE_RETURN_TYPE = new Node("RETURN_TYPE", "", yylineno);
                            $$->children.push_back(NODE_RETURN_TYPE);
                            NODE_RETURN_TYPE->children.push_back($2);
                            $$->children.push_back($3);
                            $$->children.push_back($7);
                            Node* NODE_RETURN = new Node("RETURN", "", yylineno);
                            $$->children.push_back(NODE_RETURN);
                            NODE_RETURN->children.push_back($9);
                            std::cerr << "Method Decl3" << std::endl;
                          }
                  | PUBLIC type identifier OPEN_PAREN CLOSE_PAREN OPEN_BRACE RETURN expression SEMICOLON CLOSE_BRACE {
                            $$ = new Node("METHOD_DECLARATION", "", yylineno);
                            Node* NODE_RETURN_TYPE = new Node("RETURN_TYPE", "", yylineno);
                            $$->children.push_back(NODE_RETURN_TYPE);
                            NODE_RETURN_TYPE->children.push_back($2);
                            $$->children.push_back($3);
                            Node* NODE_RETURN = new Node("RETURN", "", yylineno);
                            $$->children.push_back(NODE_RETURN);
                            NODE_RETURN->children.push_back($8);
                            std::cerr << "Method Decl4" << std::endl;
                          }

type: TYPE_INT OPEN_BRACKET CLOSE_BRACKET {  
                            $$ = new Node("TYPE_INT_ARRAY", "", yylineno); 
                            std::cerr << "Type1" << std::endl;
                            }
      | TYPE_BOOLEAN {  
                            $$ = new Node("TYPE_BOOLEAN", "", yylineno); 
                            std::cerr << "Type2" << std::endl;
                            }
      | TYPE_INT {          $$ = new Node("TYPE_INT", "", yylineno); 
                            std::cerr << "Type3" << std::endl;
                            }
      | identifier {  
                            $$ = new Node("TYPE_IDENTIFIER", "", yylineno); 
                            $$->children.push_back($1);
                            std::cerr << "Type4" << std::endl;
                            }

statement: OPEN_BRACE CLOSE_BRACE {
                            std::cerr << "Statement1" << std::endl;}
          | OPEN_BRACE statement_group CLOSE_BRACE {$$=$2; std::cerr << "Statement2" << std::endl;}

          | IF OPEN_PAREN expression CLOSE_PAREN statement ELSE statement {
                            $$ = new Node("IF_ELSE", "", yylineno);
                            $$->children.push_back($3);
                            $$->children.push_back($5);
                            $$->children.push_back($7);
                            std::cerr << "Statement3" << std::endl;
                          }
          | IF OPEN_PAREN expression CLOSE_PAREN statement {
                            $$ = new Node("IF", "", yylineno);
                            $$->children.push_back($3);
                            $$->children.push_back($5);
                            std::cerr << "Statement3.1" << std::endl;
                          }
          | WHILE OPEN_PAREN expression CLOSE_PAREN statement {
                            $$ = new Node("WHILE", "", yylineno);
                            $$->children.push_back($3);
                            $$->children.push_back($5);
                            std::cerr << "Statement4" << std::endl;
                          }
          | PRINT OPEN_PAREN expression CLOSE_PAREN SEMICOLON {
                            $$ = new Node("PRINT", "", yylineno);
                            $$->children.push_back($3);
                            std::cerr << "Statement5" << std::endl;
                          }
          | identifier ASSIGN expression SEMICOLON {
                            $$ = new Node("ASSIGN", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            std::cerr << "Statement6" << std::endl;
                          }
          | identifier OPEN_BRACKET expression CLOSE_BRACKET ASSIGN expression SEMICOLON {
                            $$ = new Node("ASSIGN", "", yylineno);
                            Node* NODE_ARRAY = new Node("ARRAY", "", yylineno);
                            $$->children.push_back(NODE_ARRAY);
                            $$->children.push_back($6);
                            NODE_ARRAY->children.push_back($1);
                            NODE_ARRAY->children.push_back($3);
                            std::cerr << "Statement7" << std::endl;
                          }

expression: expression AND expression { 
                            $$ = new Node("AND", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            std::cerr << "Expression1" << std::endl;
                          }
            | expression OR expression {
                            $$ = new Node("OR", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            std::cerr << "Expression2" << std::endl;
                          }
            | expression LESS_THAN expression {
                            $$ = new Node("<", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            std::cerr << "Expression3" << std::endl;
                          }
            | expression GREATER_THAN expression {
                            $$ = new Node(">", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            std::cerr << "Expression4" << std::endl;
                          }
            | expression EQUAL expression {
                            $$ = new Node("==", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            std::cerr << "Expression5" << std::endl;
                          }
            | expression PLUS expression {
                            $$ = new Node("+", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            std::cerr << "Expression6" << std::endl;
                          }
            | expression MINUS expression {
                            $$ = new Node("-", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            std::cerr << "Expression7" << std::endl;
                          }
            | expression MULTIPLY expression {
                            $$ = new Node("*", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            std::cerr << "Expression8" << std::endl;
                          }
            | expression DIVIDE expression {
                            $$ = new Node("/", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            std::cerr << "Expression9" << std::endl;
                          }
            | expression OPEN_BRACKET expression CLOSE_BRACKET {
                            $$ = new Node("ARRAY", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            std::cerr << "Expression10" << std::endl;
                          }
            | expression DOT LENGTH {
                            $$ = $1;
                            Node* NODE_LENGTH = new Node("LENGTH", "", yylineno);
                            $$->children.push_back(NODE_LENGTH);
                            std::cerr << "Expression11" << std::endl;
                          }
            | expression DOT identifier OPEN_PAREN expression_parameter CLOSE_PAREN {
                            $$ = $1;
                            $$->children.push_back($3);
                            $3->children.push_back($5);
                            std::cerr << "Expression12" << std::endl;
                          }
            | expression DOT identifier OPEN_PAREN CLOSE_PAREN {
                            $$ = $1;
                            $$->children.push_back($3);
                            std::cerr << "Expression12.1" << std::endl;
                          }
            | INTEGER_LITERAL { $$ = new Node("Integer_Literal", $1, yylineno); std::cerr << "Expression13" << std::endl; }
            | TRUE { $$ = new Node("TRUE", "", yylineno);  std::cerr << "Expression14" << std::endl;}
            | FALSE { $$ = new Node("FALSE", "", yylineno); std::cerr << "Expression15" << std::endl;}
            | identifier { $$ = $1; std::cerr << "Expression16" << std::endl;}
            | THIS { $$ = new Node("THIS", "", yylineno); std::cerr << "Expression17" << std::endl;}
            | NEW TYPE_INT OPEN_BRACKET expression CLOSE_BRACKET {
                            $$ = new Node("NEW_INT_ARRAY", "", yylineno);
                            $$->children.push_back($4);
                            std::cerr << "Expression18" << std::endl;
                          }
            | NEW identifier OPEN_PAREN CLOSE_PAREN {
                            $$ = new Node("NEW_IDENTIFIER", "", yylineno);
                            $$->children.push_back($2);
                            std::cerr << "Expression19" << std::endl;
                          }
            | NOT expression {
                            $$ = new Node("NOT", "", yylineno);
                            $$->children.push_back($2);
                            std::cerr << "Expression20" << std::endl;
                          }
            | OPEN_PAREN expression CLOSE_PAREN { $$ = $2; std::cerr << "Expression21" << std::endl;}
            ;

expression_parameter: expression COMMA expression {
                            $$ = new Node("EXPRESSION_PARAMETER", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            std::cerr << "Expression Param1" << std::endl;
                          }
                    | expression_parameter COMMA expression {
                            $$ = $1;
                            $$->children.push_back($3);
                            std::cerr << "Expression Param2" << std::endl;
                          }
                    | expression {$$=$1; std::cerr << "Expression Param3" << std::endl;}

identifier_parameter: identifier_parameter COMMA type identifier {
                            $$ = $1;
                            Node* NODE_PARAMETER2 = new Node("PARAMETER", "", yylineno);
                            $$->children.push_back(NODE_PARAMETER2);
                            NODE_PARAMETER2->children.push_back($3);
                            NODE_PARAMETER2->children.push_back($4);
                            std::cerr << "Identifier Param1" << std::endl;
                          }
                    | type identifier {
                            $$ = new Node("PARAMETER_LIST", "", yylineno);
                            Node* NODE_PARAMETER = new Node("PARAMETER", "", yylineno);
                            $$->children.push_back(NODE_PARAMETER);
                            NODE_PARAMETER->children.push_back($1);
                            NODE_PARAMETER->children.push_back($2);
                            std::cerr << "Identifier Param2" << std::endl;
                          }

method_body: var_declaration {
                            $$ = new Node("METHOD_BODY", "", yylineno);
                            $$->children.push_back($1);
                            std::cerr << "Method Body1" << std::endl;
                          }
            | statement {
                            $$ = new Node("METHOD_BODY", "", yylineno);
                            $$->children.push_back($1);
                            std::cerr << "Method Body2" << std::endl;
                          }
            | method_body statement {
                            $$ = $1;
                            $$->children.push_back($2);
                            std::cerr << "Method Body3" << std::endl;
                          }
            | method_body var_declaration {
                            $$ = $1;
                            $$->children.push_back($2);
                            std::cerr << "Method Body4" << std::endl;
                          }

class_body: var_declaration {
                            $$ = new Node("CLASS_BODY", "", yylineno);
                            $$->children.push_back($1);
                            std::cerr << "Class Body1" << std::endl;
                          }
            | method_declaration {
                            $$ = new Node("CLASS_BODY", "", yylineno);
                            $$->children.push_back($1);
                            std::cerr << "Class Body2" << std::endl;
                          }
            | class_body var_declaration {
                            $$ = $1;
                            $$->children.push_back($2);
                            std::cerr << "Class Body3" << std::endl;
                          }
            | class_body method_declaration {
                            $$ = $1;
                            $$->children.push_back($2);
                            std::cerr << "Class Body4" << std::endl;
                          }
statement_group: statement statement {
                            $$ = new Node("STATEMENT_GROUP", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($2);
                            std::cerr << "Statement group1" << std::endl;
                          }
                | statement_group statement {
                            $$ = $1;
                            $$->children.push_back($2);
                            std::cerr << "Statement group2" << std::endl;
                          }
                | statement {
                            $$ = new Node("STATEMENT_GROUP", "", yylineno);
                            $$->children.push_back($1);
                            std::cerr << "Statement group3" << std::endl;
                          }
identifier: IDENTIFIER {  $$ = new Node("Identifier", $1, yylineno); std::cerr << "Iden " << $1 << std::endl;}

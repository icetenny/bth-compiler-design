%skeleton "lalr1.cc" 
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor

%code requires{
  #include <string>
  #include "Node.h"
  #define USE_LEX_ONLY false //change this macro to true if you want to isolate the lexer from the parser.
  #define PRINT_BISON false
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
goal: main_class {$$ = new Node("GOAL", "", $1->lineno);
                            $$->children.push_back($1);
                            if (PRINT_BISON){std::cout << "Goal1" << std::endl;}
                          }
            | goal class_declaration {$$ = $1;
                            $$->children.push_back($2);
                            if (PRINT_BISON){std::cout << "Goal2" << std::endl;}
                          }
            


main_class: PUBLIC CLASS identifier OPEN_BRACE PUBLIC STATIC VOID MAIN OPEN_PAREN STRING OPEN_BRACKET CLOSE_BRACKET identifier CLOSE_PAREN OPEN_BRACE statement_group CLOSE_BRACE CLOSE_BRACE { 
                            $$ = new Node("MAIN_CLASS_DECLARATION", "", std::stoi($1));
                            $$->children.push_back($3);
                            Node* MAIN_CLASS_BODY = new Node("CLASS_BODY", "", $16->lineno);
                            $$->children.push_back(MAIN_CLASS_BODY);

                            Node* MAIN_CLASS_METHOD = new Node("METHOD_DECLARATION", "", std::stoi($5));
                            MAIN_CLASS_BODY->children.push_back(MAIN_CLASS_METHOD);

                            Node* NODE_RETURN_TYPE = new Node("RETURN_TYPE", "", std::stoi($7));
                            Node* v = new Node("TYPE_VOID", "", std::stoi($7));
                            NODE_RETURN_TYPE->children.push_back(v);

                            MAIN_CLASS_METHOD->children.push_back(NODE_RETURN_TYPE);
                            Node* m = new Node("Identifier", "main", std::stoi($8));
                            MAIN_CLASS_METHOD->children.push_back(m);

                            Node* p_list = new Node("PARAMETER_LIST", "", std::stoi($9));
                            Node* p = new Node("PARAMETER", "", std::stoi($9));
                            Node* str = new Node("TYPE_STRING[]", "", std::stoi($10));
                            p_list->children.push_back(p);
                            p->children.push_back(str);
                            p->children.push_back($13);

                            MAIN_CLASS_METHOD->children.push_back(p_list);

                            Node* m_body = new Node("METHOD_BODY", "", $16->lineno);
                            MAIN_CLASS_METHOD->children.push_back(m_body);
                            m_body->children.push_back($16);

                            if (PRINT_BISON){std::cout << "Main Class" << std::endl;}
                          }

class_declaration: CLASS identifier OPEN_BRACE class_body CLOSE_BRACE { 
                            $$ = new Node("CLASS_DECLARATION", "", std::stoi($1));
                            $$->children.push_back($2);
                            $$->children.push_back($4);
                            if (PRINT_BISON){std::cout << "Class Decl1" << std::endl;}
                          }
                  | CLASS identifier OPEN_BRACE CLOSE_BRACE { 
                            $$ = new Node("CLASS_DECLARATION", "", std::stoi($1));
                            $$->children.push_back($2);
                            if (PRINT_BISON){std::cout << "Class Decl2" << std::endl;}
                          }

var_declaration: type identifier SEMICOLON { 
                            $$ = new Node("VAR_DECLARATION", "", $1->lineno);
                            $$->children.push_back($1);
                            $$->children.push_back($2);
                            if (PRINT_BISON){std::cout << "Var Decl" << std::endl;}
                          }

method_declaration: PUBLIC type identifier OPEN_PAREN identifier_parameter CLOSE_PAREN OPEN_BRACE method_body RETURN expression SEMICOLON CLOSE_BRACE {
                            $$ = new Node("METHOD_DECLARATION", "", std::stoi($1));
                            Node* NODE_RETURN_TYPE = new Node("RETURN_TYPE", "", $2->lineno);
                            $$->children.push_back(NODE_RETURN_TYPE);
                            NODE_RETURN_TYPE->children.push_back($2);
                            $$->children.push_back($3);
                            $$->children.push_back($5);
                            $$->children.push_back($8);
                            Node* NODE_RETURN = new Node("RETURN", "", $2->lineno);
                            $$->children.push_back(NODE_RETURN);
                            NODE_RETURN->children.push_back($10);
                            if (PRINT_BISON){std::cout << "Method Decl1" << std::endl;}
                          }
                  | PUBLIC type identifier OPEN_PAREN identifier_parameter CLOSE_PAREN OPEN_BRACE RETURN expression SEMICOLON CLOSE_BRACE {
                            $$ = new Node("METHOD_DECLARATION", "", std::stoi($1));
                            Node* NODE_RETURN_TYPE = new Node("RETURN_TYPE", "", $2->lineno);
                            $$->children.push_back(NODE_RETURN_TYPE);
                            NODE_RETURN_TYPE->children.push_back($2);
                            $$->children.push_back($3);
                            $$->children.push_back($5);
                            Node* NODE_RETURN = new Node("RETURN", "", $2->lineno);
                            $$->children.push_back(NODE_RETURN);
                            NODE_RETURN->children.push_back($9);
                            if (PRINT_BISON){std::cout << "Method Decl2" << std::endl;}
                          }
                  | PUBLIC type identifier OPEN_PAREN CLOSE_PAREN OPEN_BRACE method_body RETURN expression SEMICOLON CLOSE_BRACE {
                            $$ = new Node("METHOD_DECLARATION", "", std::stoi($1));
                            Node* NODE_RETURN_TYPE = new Node("RETURN_TYPE", "", $2->lineno);
                            $$->children.push_back(NODE_RETURN_TYPE);
                            NODE_RETURN_TYPE->children.push_back($2);
                            $$->children.push_back($3);

                            Node* param_list = new Node("PARAMETER_LIST", "", std::stoi($4));
                            $$->children.push_back(param_list);

                            $$->children.push_back($7);
                            Node* NODE_RETURN = new Node("RETURN", "", $2->lineno);
                            $$->children.push_back(NODE_RETURN);
                            NODE_RETURN->children.push_back($9);
                            if (PRINT_BISON){std::cout << "Method Decl3" << std::endl;}
                          }
                  | PUBLIC type identifier OPEN_PAREN CLOSE_PAREN OPEN_BRACE RETURN expression SEMICOLON CLOSE_BRACE {
                            $$ = new Node("METHOD_DECLARATION", "", std::stoi($1));
                            Node* NODE_RETURN_TYPE = new Node("RETURN_TYPE", "", $2->lineno);
                            $$->children.push_back(NODE_RETURN_TYPE);
                            NODE_RETURN_TYPE->children.push_back($2);
                            $$->children.push_back($3);

                            Node* param_list = new Node("PARAMETER_LIST", "", std::stoi($4));
                            $$->children.push_back(param_list);

                            Node* NODE_RETURN = new Node("RETURN", "", $2->lineno);
                            $$->children.push_back(NODE_RETURN);
                            NODE_RETURN->children.push_back($8);
                            if (PRINT_BISON){std::cout << "Method Decl4" << std::endl;}
                          }

type: TYPE_INT OPEN_BRACKET CLOSE_BRACKET {  
                            $$ = new Node("TYPE_INT_ARRAY", "", std::stoi($1)); 
                            if (PRINT_BISON){std::cout << "Type1" << std::endl;}
                            }
      | TYPE_BOOLEAN {  
                            $$ = new Node("TYPE_BOOLEAN", "", std::stoi($1)); 
                            if (PRINT_BISON){std::cout << "Type2" << std::endl;}
                            }
      | TYPE_INT {          $$ = new Node("TYPE_INT", "", std::stoi($1)); 
                            if (PRINT_BISON){std::cout << "Type3" << std::endl;}
                            }
      | identifier {  
                            $$ = new Node($1->value, "", $1->lineno); 
                            if (PRINT_BISON){std::cout << "Type4" << std::endl;}
                            }

statement: OPEN_BRACE CLOSE_BRACE {
                            $$ = new Node("STATEMENT", "STATEMENT_GROUP", std::stoi($1));
                            if (PRINT_BISON){std::cout << "Statement1" << std::endl;}}
          | OPEN_BRACE statement_group CLOSE_BRACE {$$=$2; if (PRINT_BISON){std::cout << "Statement2" << std::endl;}}

          | IF OPEN_PAREN expression CLOSE_PAREN statement ELSE statement {
                            $$ = new Node("STATEMENT", "IF_ELSE", std::stoi($1));
                            $$->children.push_back($3);
                            $$->children.push_back($5);
                            $$->children.push_back($7);
                            if (PRINT_BISON){std::cout << "Statement3" << std::endl;}
                          }
          | IF OPEN_PAREN expression CLOSE_PAREN statement {
                            $$ = new Node("STATEMENT", "IF", std::stoi($1));
                            $$->children.push_back($3);
                            $$->children.push_back($5);
                            if (PRINT_BISON){std::cout << "Statement3.1" << std::endl;}
                          }
          | WHILE OPEN_PAREN expression CLOSE_PAREN statement {
                            $$ = new Node("STATEMENT", "WHILE", std::stoi($1));
                            $$->children.push_back($3);
                            $$->children.push_back($5);
                            if (PRINT_BISON){std::cout << "Statement4" << std::endl;}
                          }
          | PRINT OPEN_PAREN expression CLOSE_PAREN SEMICOLON {
                            $$ = new Node("STATEMENT", "PRINT", std::stoi($1));
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Statement5" << std::endl;}
                          }
          | identifier ASSIGN expression SEMICOLON {
                            $$ = new Node("STATEMENT", "ASSIGN", std::stoi($2));
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Statement6" << std::endl;}
                          }
          | identifier OPEN_BRACKET expression CLOSE_BRACKET ASSIGN expression SEMICOLON {
                            $$ = new Node("STATEMENT", "ASSIGN", std::stoi($5));
                            Node* NODE_ARRAY = new Node("ARRAY_INDEX", "", std::stoi($2));
                            $$->children.push_back(NODE_ARRAY);
                            $$->children.push_back($6);
                            NODE_ARRAY->children.push_back($1);
                            NODE_ARRAY->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Statement7" << std::endl;}
                          }

expression: expression AND expression { 
                            $$ = new Node("EXPRESSION", "AND", std::stoi($2));
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Expression1" << std::endl;}
                          }
            | expression OR expression {
                            $$ = new Node("EXPRESSION", "OR", std::stoi($2));
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Expression2" << std::endl;}
                          }
            | expression LESS_THAN expression {
                            $$ = new Node("EXPRESSION", "<", std::stoi($2));
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Expression3" << std::endl;}
                          }
            | expression GREATER_THAN expression {
                            $$ = new Node("EXPRESSION", ">", std::stoi($2));
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Expression4" << std::endl;}
                          }
            | expression EQUAL expression {
                            $$ = new Node("EXPRESSION", "==", std::stoi($2));
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Expression5" << std::endl;}
                          }
            | expression PLUS expression {
                            $$ = new Node("EXPRESSION", "+", std::stoi($2));
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Expression6" << std::endl;}
                          }
            | expression MINUS expression {
                            $$ = new Node("EXPRESSION", "-", std::stoi($2));
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Expression7" << std::endl;}
                          }
            | expression MULTIPLY expression {
                            $$ = new Node("EXPRESSION", "*", std::stoi($2));
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Expression8" << std::endl;}
                          }
            | expression DIVIDE expression {
                            $$ = new Node("EXPRESSION", "/", std::stoi($2));
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Expression9" << std::endl;}
                          }
            | expression OPEN_BRACKET expression CLOSE_BRACKET {
                            $$ = new Node("EXPRESSION", "ARRAY_INDEX", std::stoi($2));
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Expression10" << std::endl;}
                          }
            | expression DOT LENGTH {
                            $$ = new Node("EXPRESSION", "LENGTH", std::stoi($3));
                            $$->children.push_back($1);
                            if (PRINT_BISON){std::cout << "Expression11" << std::endl;}
                          }
            | expression DOT identifier OPEN_PAREN expression_parameter CLOSE_PAREN {
                            $$ = new Node("EXPRESSION", "CALL_FUNCTION", std::stoi($2));
                            $$->children.push_back($1);

                            Node* m = new Node("EXPRESSION", "CALL_METHOD", $3->lineno);
                            m->children.push_back($3);
                            $$->children.push_back(m);
                            $$->children.push_back($5);
                            if (PRINT_BISON){std::cout << "Expression12" << std::endl;}
                          }
            /* | expression DOT identifier OPEN_PAREN CLOSE_PAREN {
                            $$ = $1;
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Expression12.1" << std::endl;}
                          } */
            | INTEGER_LITERAL { $$ = new Node("Integer_Literal", $1, yylineno); if (PRINT_BISON){std::cout << "Expression13" << std::endl;} }
            | TRUE { $$ = new Node("EXPRESSION", "TRUE", std::stoi($1));  if (PRINT_BISON){std::cout << "Expression14" << std::endl;}}
            | FALSE { $$ = new Node("EXPRESSION", "FALSE", std::stoi($1)); if (PRINT_BISON){std::cout << "Expression15" << std::endl;}}
            | identifier { $$ = $1; if (PRINT_BISON){std::cout << "Expression16" << std::endl;}}
            | THIS { $$ = new Node("EXPRESSION", "THIS", std::stoi($1)); if (PRINT_BISON){std::cout << "Expression17" << std::endl;}}
            | NEW TYPE_INT OPEN_BRACKET expression CLOSE_BRACKET {
                            $$ = new Node("EXPRESSION", "NEW_INT_ARRAY", std::stoi($1));
                            $$->children.push_back($4);
                            if (PRINT_BISON){std::cout << "Expression18" << std::endl;}
                          }
            | NEW identifier OPEN_PAREN CLOSE_PAREN {
                            $$ = new Node("EXPRESSION", "NEW_CLASS_OBJECT", std::stoi($1));
                            $$->children.push_back($2);
                            if (PRINT_BISON){std::cout << "Expression19" << std::endl;}
                          }
            | NOT expression {
                            $$ = new Node("EXPRESSION", "NOT", std::stoi($1));
                            $$->children.push_back($2);
                            if (PRINT_BISON){std::cout << "Expression20" << std::endl;}
                          }
            | OPEN_PAREN expression CLOSE_PAREN { $$ = $2; if (PRINT_BISON){std::cout << "Expression21" << std::endl;}}
            ;

expression_parameter: expression COMMA expression {
                            $$ = new Node("EXPRESSION_PARAMETER", "", std::stoi($2));
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Expression Param1" << std::endl;}
                          }
                    | expression_parameter COMMA expression {
                            $$ = $1;
                            $$->children.push_back($3);
                            if (PRINT_BISON){std::cout << "Expression Param2" << std::endl;}
                          }
                    | expression {
                            $$ = new Node("EXPRESSION_PARAMETER", "", $1->lineno);
                            $$->children.push_back($1);
                            if (PRINT_BISON){std::cout << "Expression Param3" << std::endl;}
                          }
                    | /* empty */ {
                            $$ = new Node("EXPRESSION_PARAMETER", "", yylineno);
                            if (PRINT_BISON){std::cout << "Expression Param4" << std::endl;}

                          }

identifier_parameter: identifier_parameter COMMA type identifier {
                            $$ = $1;
                            Node* NODE_PARAMETER2 = new Node("PARAMETER", "", $1->lineno);
                            $$->children.push_back(NODE_PARAMETER2);
                            NODE_PARAMETER2->children.push_back($3);
                            NODE_PARAMETER2->children.push_back($4);
                            if (PRINT_BISON){std::cout << "Identifier Param1" << std::endl;}
                          }
                    | type identifier {
                            $$ = new Node("PARAMETER_LIST", "", $1->lineno);
                            Node* NODE_PARAMETER = new Node("PARAMETER", "", $1->lineno);
                            $$->children.push_back(NODE_PARAMETER);
                            NODE_PARAMETER->children.push_back($1);
                            NODE_PARAMETER->children.push_back($2);
                            if (PRINT_BISON){std::cout << "Identifier Param2" << std::endl;}
                          }

method_body: var_declaration {
                            $$ = new Node("METHOD_BODY", "", $1->lineno);
                            $$->children.push_back($1);
                            if (PRINT_BISON){std::cout << "Method Body1" << std::endl;}
                          }
            | statement {
                            $$ = new Node("METHOD_BODY", "", $1->lineno);
                            $$->children.push_back($1);
                            if (PRINT_BISON){std::cout << "Method Body2" << std::endl;}
                          }
            | method_body statement {
                            $$ = $1;
                            $$->children.push_back($2);
                            if (PRINT_BISON){std::cout << "Method Body3" << std::endl;}
                          }
            | method_body var_declaration {
                            $$ = $1;
                            $$->children.push_back($2);
                            if (PRINT_BISON){std::cout << "Method Body4" << std::endl;}
                          }

class_body: var_declaration {
                            $$ = new Node("CLASS_BODY", "", $1->lineno);
                            $$->children.push_back($1);
                            if (PRINT_BISON){std::cout << "Class Body1" << std::endl;}
                          }
            | method_declaration {
                            $$ = new Node("CLASS_BODY", "", $1->lineno);
                            $$->children.push_back($1);
                            if (PRINT_BISON){std::cout << "Class Body2" << std::endl;}
                          }
            | class_body var_declaration {
                            $$ = $1;
                            $$->children.push_back($2);
                            if (PRINT_BISON){std::cout << "Class Body3" << std::endl;}
                          }
            | class_body method_declaration {
                            $$ = $1;
                            $$->children.push_back($2);
                            if (PRINT_BISON){std::cout << "Class Body4" << std::endl;}
                          }
statement_group: statement statement {
                            $$ = new Node("STATEMENT", "STATEMENT_GROUP", $1->lineno);
                            $$->children.push_back($1);
                            $$->children.push_back($2);
                            if (PRINT_BISON){std::cout << "Statement group1" << std::endl;}
                          }
                | statement_group statement {
                            $$ = $1;
                            $$->children.push_back($2);
                            if (PRINT_BISON){std::cout << "Statement group2" << std::endl;}
                          }
                | statement {
                            $$ = new Node("STATEMENT", "STATEMENT_GROUP", $1->lineno);
                            $$->children.push_back($1);
                            if (PRINT_BISON){std::cout << "Statement group3" << std::endl;}
                          }
identifier: IDENTIFIER {  $$ = new Node("Identifier", $1, yylineno); if (PRINT_BISON){std::cout << "Iden " << $1 << std::endl;}}

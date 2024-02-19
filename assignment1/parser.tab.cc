// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 13 "parser.yy"

  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;
  
  Node* root;
  extern int yylineno;

#line 54 "parser.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 127 "parser.tab.cc"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_goal: // goal
      case symbol_kind::S_main_class: // main_class
      case symbol_kind::S_class_declaration: // class_declaration
      case symbol_kind::S_var_declaration: // var_declaration
      case symbol_kind::S_method_declaration: // method_declaration
      case symbol_kind::S_type: // type
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expression_parameter: // expression_parameter
      case symbol_kind::S_identifier_parameter: // identifier_parameter
      case symbol_kind::S_method_body: // method_body
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_statement_group: // statement_group
      case symbol_kind::S_identifier: // identifier
        value.YY_MOVE_OR_COPY< Node * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_TYPE_INT: // TYPE_INT
      case symbol_kind::S_TYPE_BOOLEAN: // TYPE_BOOLEAN
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_OPEN_BRACE: // OPEN_BRACE
      case symbol_kind::S_CLOSE_BRACE: // CLOSE_BRACE
      case symbol_kind::S_OPEN_PAREN: // OPEN_PAREN
      case symbol_kind::S_CLOSE_PAREN: // CLOSE_PAREN
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_OPEN_BRACKET: // OPEN_BRACKET
      case symbol_kind::S_CLOSE_BRACKET: // CLOSE_BRACKET
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_MULTIPLY: // MULTIPLY
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
      case symbol_kind::S_WS: // WS
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_goal: // goal
      case symbol_kind::S_main_class: // main_class
      case symbol_kind::S_class_declaration: // class_declaration
      case symbol_kind::S_var_declaration: // var_declaration
      case symbol_kind::S_method_declaration: // method_declaration
      case symbol_kind::S_type: // type
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expression_parameter: // expression_parameter
      case symbol_kind::S_identifier_parameter: // identifier_parameter
      case symbol_kind::S_method_body: // method_body
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_statement_group: // statement_group
      case symbol_kind::S_identifier: // identifier
        value.move< Node * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_TYPE_INT: // TYPE_INT
      case symbol_kind::S_TYPE_BOOLEAN: // TYPE_BOOLEAN
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_OPEN_BRACE: // OPEN_BRACE
      case symbol_kind::S_CLOSE_BRACE: // CLOSE_BRACE
      case symbol_kind::S_OPEN_PAREN: // OPEN_PAREN
      case symbol_kind::S_CLOSE_PAREN: // CLOSE_PAREN
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_OPEN_BRACKET: // OPEN_BRACKET
      case symbol_kind::S_CLOSE_BRACKET: // CLOSE_BRACKET
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_MULTIPLY: // MULTIPLY
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
      case symbol_kind::S_WS: // WS
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_goal: // goal
      case symbol_kind::S_main_class: // main_class
      case symbol_kind::S_class_declaration: // class_declaration
      case symbol_kind::S_var_declaration: // var_declaration
      case symbol_kind::S_method_declaration: // method_declaration
      case symbol_kind::S_type: // type
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expression_parameter: // expression_parameter
      case symbol_kind::S_identifier_parameter: // identifier_parameter
      case symbol_kind::S_method_body: // method_body
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_statement_group: // statement_group
      case symbol_kind::S_identifier: // identifier
        value.copy< Node * > (that.value);
        break;

      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_TYPE_INT: // TYPE_INT
      case symbol_kind::S_TYPE_BOOLEAN: // TYPE_BOOLEAN
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_OPEN_BRACE: // OPEN_BRACE
      case symbol_kind::S_CLOSE_BRACE: // CLOSE_BRACE
      case symbol_kind::S_OPEN_PAREN: // OPEN_PAREN
      case symbol_kind::S_CLOSE_PAREN: // CLOSE_PAREN
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_OPEN_BRACKET: // OPEN_BRACKET
      case symbol_kind::S_CLOSE_BRACKET: // CLOSE_BRACKET
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_MULTIPLY: // MULTIPLY
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
      case symbol_kind::S_WS: // WS
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_goal: // goal
      case symbol_kind::S_main_class: // main_class
      case symbol_kind::S_class_declaration: // class_declaration
      case symbol_kind::S_var_declaration: // var_declaration
      case symbol_kind::S_method_declaration: // method_declaration
      case symbol_kind::S_type: // type
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expression_parameter: // expression_parameter
      case symbol_kind::S_identifier_parameter: // identifier_parameter
      case symbol_kind::S_method_body: // method_body
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_statement_group: // statement_group
      case symbol_kind::S_identifier: // identifier
        value.move< Node * > (that.value);
        break;

      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_TYPE_INT: // TYPE_INT
      case symbol_kind::S_TYPE_BOOLEAN: // TYPE_BOOLEAN
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_OPEN_BRACE: // OPEN_BRACE
      case symbol_kind::S_CLOSE_BRACE: // CLOSE_BRACE
      case symbol_kind::S_OPEN_PAREN: // OPEN_PAREN
      case symbol_kind::S_CLOSE_PAREN: // CLOSE_PAREN
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_OPEN_BRACKET: // OPEN_BRACKET
      case symbol_kind::S_CLOSE_BRACKET: // CLOSE_BRACKET
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_MULTIPLY: // MULTIPLY
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
      case symbol_kind::S_WS: // WS
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_goal: // goal
      case symbol_kind::S_main_class: // main_class
      case symbol_kind::S_class_declaration: // class_declaration
      case symbol_kind::S_var_declaration: // var_declaration
      case symbol_kind::S_method_declaration: // method_declaration
      case symbol_kind::S_type: // type
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expression_parameter: // expression_parameter
      case symbol_kind::S_identifier_parameter: // identifier_parameter
      case symbol_kind::S_method_body: // method_body
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_statement_group: // statement_group
      case symbol_kind::S_identifier: // identifier
        yylhs.value.emplace< Node * > ();
        break;

      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_TYPE_INT: // TYPE_INT
      case symbol_kind::S_TYPE_BOOLEAN: // TYPE_BOOLEAN
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_LENGTH: // LENGTH
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_OPEN_BRACE: // OPEN_BRACE
      case symbol_kind::S_CLOSE_BRACE: // CLOSE_BRACE
      case symbol_kind::S_OPEN_PAREN: // OPEN_PAREN
      case symbol_kind::S_CLOSE_PAREN: // CLOSE_PAREN
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_OPEN_BRACKET: // OPEN_BRACKET
      case symbol_kind::S_CLOSE_BRACKET: // CLOSE_BRACKET
      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_MULTIPLY: // MULTIPLY
      case symbol_kind::S_DIVIDE: // DIVIDE
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER_LITERAL: // INTEGER_LITERAL
      case symbol_kind::S_WS: // WS
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // root: goal "end of file"
#line 36 "parser.yy"
                     {root = yystack_[1].value.as < Node * > ();}
#line 818 "parser.tab.cc"
    break;

  case 3: // goal: main_class
#line 37 "parser.yy"
                 {yylhs.value.as < Node * > () = new Node("GOAL", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Goal1" << std::endl;
                          }
#line 827 "parser.tab.cc"
    break;

  case 4: // goal: goal class_declaration
#line 41 "parser.yy"
                                     {yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Goal2" << std::endl;
                          }
#line 836 "parser.tab.cc"
    break;

  case 5: // main_class: PUBLIC CLASS identifier OPEN_BRACE PUBLIC STATIC VOID MAIN OPEN_PAREN STRING OPEN_BRACKET CLOSE_BRACKET identifier CLOSE_PAREN OPEN_BRACE statement_group CLOSE_BRACE CLOSE_BRACE
#line 48 "parser.yy"
                                                                                                                                                                                              { 
                            yylhs.value.as < Node * > () = new Node("MAIN_CLASS", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[15].value.as < Node * > ());
                            Node* MAIN_CLASS_METHOD = new Node("MAIN_CLASS_METHOD", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(MAIN_CLASS_METHOD);
                            MAIN_CLASS_METHOD->children.push_back(yystack_[5].value.as < Node * > ());
                            MAIN_CLASS_METHOD->children.push_back(yystack_[2].value.as < Node * > ());
                            std::cerr << "Main Class" << std::endl;
                          }
#line 850 "parser.tab.cc"
    break;

  case 6: // class_declaration: CLASS identifier OPEN_BRACE class_body CLOSE_BRACE
#line 58 "parser.yy"
                                                                      { 
                            yylhs.value.as < Node * > () = new Node("CLASS_DECLARATION", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
                            std::cerr << "Class Decl1" << std::endl;
                          }
#line 861 "parser.tab.cc"
    break;

  case 7: // class_declaration: CLASS identifier OPEN_BRACE CLOSE_BRACE
#line 64 "parser.yy"
                                                            { 
                            yylhs.value.as < Node * > () = new Node("CLASS_DECLARATION", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            std::cerr << "Class Decl2" << std::endl;
                          }
#line 871 "parser.tab.cc"
    break;

  case 8: // var_declaration: type identifier SEMICOLON
#line 70 "parser.yy"
                                           { 
                            yylhs.value.as < Node * > () = new Node("VAR_DECLARATION", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
                            std::cerr << "Var Decl" << std::endl;
                          }
#line 882 "parser.tab.cc"
    break;

  case 9: // method_declaration: PUBLIC type identifier OPEN_PAREN identifier_parameter CLOSE_PAREN OPEN_BRACE method_body RETURN expression SEMICOLON CLOSE_BRACE
#line 77 "parser.yy"
                                                                                                                                                      {
                            yylhs.value.as < Node * > () = new Node("METHOD_DECLARATION", "", yylineno);
                            Node* NODE_RETURN_TYPE = new Node("RETURN_TYPE", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(NODE_RETURN_TYPE);
                            NODE_RETURN_TYPE->children.push_back(yystack_[10].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[9].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[7].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());
                            Node* NODE_RETURN = new Node("RETURN", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(NODE_RETURN);
                            NODE_RETURN->children.push_back(yystack_[2].value.as < Node * > ());
                            std::cerr << "Method Decl1" << std::endl;
                          }
#line 900 "parser.tab.cc"
    break;

  case 10: // method_declaration: PUBLIC type identifier OPEN_PAREN identifier_parameter CLOSE_PAREN OPEN_BRACE RETURN expression SEMICOLON CLOSE_BRACE
#line 90 "parser.yy"
                                                                                                                                          {
                            yylhs.value.as < Node * > () = new Node("METHOD_DECLARATION", "", yylineno);
                            Node* NODE_RETURN_TYPE = new Node("RETURN_TYPE", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(NODE_RETURN_TYPE);
                            NODE_RETURN_TYPE->children.push_back(yystack_[9].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[8].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[6].value.as < Node * > ());
                            Node* NODE_RETURN = new Node("RETURN", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(NODE_RETURN);
                            NODE_RETURN->children.push_back(yystack_[2].value.as < Node * > ());
                            std::cerr << "Method Decl2" << std::endl;
                          }
#line 917 "parser.tab.cc"
    break;

  case 11: // method_declaration: PUBLIC type identifier OPEN_PAREN CLOSE_PAREN OPEN_BRACE method_body RETURN expression SEMICOLON CLOSE_BRACE
#line 102 "parser.yy"
                                                                                                                                 {
                            yylhs.value.as < Node * > () = new Node("METHOD_DECLARATION", "", yylineno);
                            Node* NODE_RETURN_TYPE = new Node("RETURN_TYPE", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(NODE_RETURN_TYPE);
                            NODE_RETURN_TYPE->children.push_back(yystack_[9].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[8].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());
                            Node* NODE_RETURN = new Node("RETURN", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(NODE_RETURN);
                            NODE_RETURN->children.push_back(yystack_[2].value.as < Node * > ());
                            std::cerr << "Method Decl3" << std::endl;
                          }
#line 934 "parser.tab.cc"
    break;

  case 12: // method_declaration: PUBLIC type identifier OPEN_PAREN CLOSE_PAREN OPEN_BRACE RETURN expression SEMICOLON CLOSE_BRACE
#line 114 "parser.yy"
                                                                                                                     {
                            yylhs.value.as < Node * > () = new Node("METHOD_DECLARATION", "", yylineno);
                            Node* NODE_RETURN_TYPE = new Node("RETURN_TYPE", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(NODE_RETURN_TYPE);
                            NODE_RETURN_TYPE->children.push_back(yystack_[8].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[7].value.as < Node * > ());
                            Node* NODE_RETURN = new Node("RETURN", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(NODE_RETURN);
                            NODE_RETURN->children.push_back(yystack_[2].value.as < Node * > ());
                            std::cerr << "Method Decl4" << std::endl;
                          }
#line 950 "parser.tab.cc"
    break;

  case 13: // type: TYPE_INT OPEN_BRACKET CLOSE_BRACKET
#line 126 "parser.yy"
                                          {  
                            yylhs.value.as < Node * > () = new Node("TYPE_INT_ARRAY", "", yylineno); 
                            std::cerr << "Type1" << std::endl;
                            }
#line 959 "parser.tab.cc"
    break;

  case 14: // type: TYPE_BOOLEAN
#line 130 "parser.yy"
                     {  
                            yylhs.value.as < Node * > () = new Node("TYPE_BOOLEAN", "", yylineno); 
                            std::cerr << "Type2" << std::endl;
                            }
#line 968 "parser.tab.cc"
    break;

  case 15: // type: TYPE_INT
#line 134 "parser.yy"
                 {          yylhs.value.as < Node * > () = new Node("TYPE_INT", "", yylineno); 
                            std::cerr << "Type3" << std::endl;
                            }
#line 976 "parser.tab.cc"
    break;

  case 16: // type: identifier
#line 137 "parser.yy"
                   {  
                            yylhs.value.as < Node * > () = new Node("TYPE_IDENTIFIER", "", yylineno); 
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Type4" << std::endl;
                            }
#line 986 "parser.tab.cc"
    break;

  case 17: // statement: OPEN_BRACE CLOSE_BRACE
#line 143 "parser.yy"
                                  {
                            std::cerr << "Statement1" << std::endl;}
#line 993 "parser.tab.cc"
    break;

  case 18: // statement: OPEN_BRACE statement_group CLOSE_BRACE
#line 145 "parser.yy"
                                                   {yylhs.value.as < Node * > ()=yystack_[1].value.as < Node * > (); std::cerr << "Statement2" << std::endl;}
#line 999 "parser.tab.cc"
    break;

  case 19: // statement: IF OPEN_PAREN expression CLOSE_PAREN statement ELSE statement
#line 147 "parser.yy"
                                                                          {
                            yylhs.value.as < Node * > () = new Node("IF_ELSE", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Statement3" << std::endl;
                          }
#line 1011 "parser.tab.cc"
    break;

  case 20: // statement: IF OPEN_PAREN expression CLOSE_PAREN statement
#line 154 "parser.yy"
                                                           {
                            yylhs.value.as < Node * > () = new Node("IF", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Statement3.1" << std::endl;
                          }
#line 1022 "parser.tab.cc"
    break;

  case 21: // statement: WHILE OPEN_PAREN expression CLOSE_PAREN statement
#line 160 "parser.yy"
                                                              {
                            yylhs.value.as < Node * > () = new Node("WHILE", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Statement4" << std::endl;
                          }
#line 1033 "parser.tab.cc"
    break;

  case 22: // statement: PRINT OPEN_PAREN expression CLOSE_PAREN SEMICOLON
#line 166 "parser.yy"
                                                              {
                            yylhs.value.as < Node * > () = new Node("PRINT", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            std::cerr << "Statement5" << std::endl;
                          }
#line 1043 "parser.tab.cc"
    break;

  case 23: // statement: identifier ASSIGN expression SEMICOLON
#line 171 "parser.yy"
                                                   {
                            yylhs.value.as < Node * > () = new Node("ASSIGN", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
                            std::cerr << "Statement6" << std::endl;
                          }
#line 1054 "parser.tab.cc"
    break;

  case 24: // statement: identifier OPEN_BRACKET expression CLOSE_BRACKET ASSIGN expression SEMICOLON
#line 177 "parser.yy"
                                                                                         {
                            yylhs.value.as < Node * > () = new Node("ASSIGN", "", yylineno);
                            Node* NODE_ARRAY = new Node("ARRAY", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(NODE_ARRAY);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
                            NODE_ARRAY->children.push_back(yystack_[6].value.as < Node * > ());
                            NODE_ARRAY->children.push_back(yystack_[4].value.as < Node * > ());
                            std::cerr << "Statement7" << std::endl;
                          }
#line 1068 "parser.tab.cc"
    break;

  case 25: // expression: expression AND expression
#line 187 "parser.yy"
                                      { 
                            yylhs.value.as < Node * > () = new Node("AND", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Expression1" << std::endl;
                          }
#line 1079 "parser.tab.cc"
    break;

  case 26: // expression: expression OR expression
#line 193 "parser.yy"
                                       {
                            yylhs.value.as < Node * > () = new Node("OR", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Expression2" << std::endl;
                          }
#line 1090 "parser.tab.cc"
    break;

  case 27: // expression: expression LESS_THAN expression
#line 199 "parser.yy"
                                              {
                            yylhs.value.as < Node * > () = new Node("<", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Expression3" << std::endl;
                          }
#line 1101 "parser.tab.cc"
    break;

  case 28: // expression: expression GREATER_THAN expression
#line 205 "parser.yy"
                                                 {
                            yylhs.value.as < Node * > () = new Node(">", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Expression4" << std::endl;
                          }
#line 1112 "parser.tab.cc"
    break;

  case 29: // expression: expression EQUAL expression
#line 211 "parser.yy"
                                          {
                            yylhs.value.as < Node * > () = new Node("==", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Expression5" << std::endl;
                          }
#line 1123 "parser.tab.cc"
    break;

  case 30: // expression: expression PLUS expression
#line 217 "parser.yy"
                                         {
                            yylhs.value.as < Node * > () = new Node("+", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Expression6" << std::endl;
                          }
#line 1134 "parser.tab.cc"
    break;

  case 31: // expression: expression MINUS expression
#line 223 "parser.yy"
                                          {
                            yylhs.value.as < Node * > () = new Node("-", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Expression7" << std::endl;
                          }
#line 1145 "parser.tab.cc"
    break;

  case 32: // expression: expression MULTIPLY expression
#line 229 "parser.yy"
                                             {
                            yylhs.value.as < Node * > () = new Node("*", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Expression8" << std::endl;
                          }
#line 1156 "parser.tab.cc"
    break;

  case 33: // expression: expression DIVIDE expression
#line 235 "parser.yy"
                                           {
                            yylhs.value.as < Node * > () = new Node("/", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Expression9" << std::endl;
                          }
#line 1167 "parser.tab.cc"
    break;

  case 34: // expression: expression OPEN_BRACKET expression CLOSE_BRACKET
#line 241 "parser.yy"
                                                               {
                            yylhs.value.as < Node * > () = new Node("ARRAY", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
                            std::cerr << "Expression10" << std::endl;
                          }
#line 1178 "parser.tab.cc"
    break;

  case 35: // expression: expression DOT LENGTH
#line 247 "parser.yy"
                                    {
                            yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > ();
                            Node* NODE_LENGTH = new Node("LENGTH", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(NODE_LENGTH);
                            std::cerr << "Expression11" << std::endl;
                          }
#line 1189 "parser.tab.cc"
    break;

  case 36: // expression: expression DOT identifier OPEN_PAREN expression_parameter CLOSE_PAREN
#line 253 "parser.yy"
                                                                                    {
                            yylhs.value.as < Node * > () = yystack_[5].value.as < Node * > ();
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
                            yystack_[3].value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
                            std::cerr << "Expression12" << std::endl;
                          }
#line 1200 "parser.tab.cc"
    break;

  case 37: // expression: expression DOT identifier OPEN_PAREN CLOSE_PAREN
#line 259 "parser.yy"
                                                               {
                            yylhs.value.as < Node * > () = yystack_[4].value.as < Node * > ();
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            std::cerr << "Expression12.1" << std::endl;
                          }
#line 1210 "parser.tab.cc"
    break;

  case 38: // expression: INTEGER_LITERAL
#line 264 "parser.yy"
                              { yylhs.value.as < Node * > () = new Node("Integer_Literal", yystack_[0].value.as < std::string > (), yylineno); std::cerr << "Expression13" << std::endl; }
#line 1216 "parser.tab.cc"
    break;

  case 39: // expression: TRUE
#line 265 "parser.yy"
                   { yylhs.value.as < Node * > () = new Node("TRUE", "", yylineno);  std::cerr << "Expression14" << std::endl;}
#line 1222 "parser.tab.cc"
    break;

  case 40: // expression: FALSE
#line 266 "parser.yy"
                    { yylhs.value.as < Node * > () = new Node("FALSE", "", yylineno); std::cerr << "Expression15" << std::endl;}
#line 1228 "parser.tab.cc"
    break;

  case 41: // expression: identifier
#line 267 "parser.yy"
                         { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); std::cerr << "Expression16" << std::endl;}
#line 1234 "parser.tab.cc"
    break;

  case 42: // expression: THIS
#line 268 "parser.yy"
                   { yylhs.value.as < Node * > () = new Node("THIS", "", yylineno); std::cerr << "Expression17" << std::endl;}
#line 1240 "parser.tab.cc"
    break;

  case 43: // expression: NEW TYPE_INT OPEN_BRACKET expression CLOSE_BRACKET
#line 269 "parser.yy"
                                                                 {
                            yylhs.value.as < Node * > () = new Node("NEW_INT_ARRAY", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
                            std::cerr << "Expression18" << std::endl;
                          }
#line 1250 "parser.tab.cc"
    break;

  case 44: // expression: NEW identifier OPEN_PAREN CLOSE_PAREN
#line 274 "parser.yy"
                                                    {
                            yylhs.value.as < Node * > () = new Node("NEW_IDENTIFIER", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            std::cerr << "Expression19" << std::endl;
                          }
#line 1260 "parser.tab.cc"
    break;

  case 45: // expression: NOT expression
#line 279 "parser.yy"
                             {
                            yylhs.value.as < Node * > () = new Node("NOT", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Expression20" << std::endl;
                          }
#line 1270 "parser.tab.cc"
    break;

  case 46: // expression: OPEN_PAREN expression CLOSE_PAREN
#line 284 "parser.yy"
                                                { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); std::cerr << "Expression21" << std::endl;}
#line 1276 "parser.tab.cc"
    break;

  case 47: // expression_parameter: expression COMMA expression
#line 287 "parser.yy"
                                                  {
                            yylhs.value.as < Node * > () = new Node("EXPRESSION_PARAMETER", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Expression Param1" << std::endl;
                          }
#line 1287 "parser.tab.cc"
    break;

  case 48: // expression_parameter: expression_parameter COMMA expression
#line 293 "parser.yy"
                                                            {
                            yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > ();
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Expression Param2" << std::endl;
                          }
#line 1297 "parser.tab.cc"
    break;

  case 49: // expression_parameter: expression
#line 298 "parser.yy"
                                 {yylhs.value.as < Node * > ()=yystack_[0].value.as < Node * > (); std::cerr << "Expression Param3" << std::endl;}
#line 1303 "parser.tab.cc"
    break;

  case 50: // identifier_parameter: identifier_parameter COMMA type identifier
#line 300 "parser.yy"
                                                                 {
                            yylhs.value.as < Node * > () = yystack_[3].value.as < Node * > ();
                            Node* NODE_PARAMETER2 = new Node("PARAMETER", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(NODE_PARAMETER2);
                            NODE_PARAMETER2->children.push_back(yystack_[1].value.as < Node * > ());
                            NODE_PARAMETER2->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Identifier Param1" << std::endl;
                          }
#line 1316 "parser.tab.cc"
    break;

  case 51: // identifier_parameter: type identifier
#line 308 "parser.yy"
                                      {
                            yylhs.value.as < Node * > () = new Node("PARAMETER_LIST", "", yylineno);
                            Node* NODE_PARAMETER = new Node("PARAMETER", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(NODE_PARAMETER);
                            NODE_PARAMETER->children.push_back(yystack_[1].value.as < Node * > ());
                            NODE_PARAMETER->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Identifier Param2" << std::endl;
                          }
#line 1329 "parser.tab.cc"
    break;

  case 52: // method_body: var_declaration
#line 317 "parser.yy"
                             {
                            yylhs.value.as < Node * > () = new Node("METHOD_BODY", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Method Body1" << std::endl;
                          }
#line 1339 "parser.tab.cc"
    break;

  case 53: // method_body: statement
#line 322 "parser.yy"
                        {
                            yylhs.value.as < Node * > () = new Node("METHOD_BODY", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Method Body2" << std::endl;
                          }
#line 1349 "parser.tab.cc"
    break;

  case 54: // method_body: method_body statement
#line 327 "parser.yy"
                                    {
                            yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Method Body3" << std::endl;
                          }
#line 1359 "parser.tab.cc"
    break;

  case 55: // method_body: method_body var_declaration
#line 332 "parser.yy"
                                          {
                            yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Method Body4" << std::endl;
                          }
#line 1369 "parser.tab.cc"
    break;

  case 56: // class_body: var_declaration
#line 338 "parser.yy"
                            {
                            yylhs.value.as < Node * > () = new Node("CLASS_BODY", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Class Body1" << std::endl;
                          }
#line 1379 "parser.tab.cc"
    break;

  case 57: // class_body: method_declaration
#line 343 "parser.yy"
                                 {
                            yylhs.value.as < Node * > () = new Node("CLASS_BODY", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Class Body2" << std::endl;
                          }
#line 1389 "parser.tab.cc"
    break;

  case 58: // class_body: class_body var_declaration
#line 348 "parser.yy"
                                         {
                            yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Class Body3" << std::endl;
                          }
#line 1399 "parser.tab.cc"
    break;

  case 59: // class_body: class_body method_declaration
#line 353 "parser.yy"
                                            {
                            yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Class Body4" << std::endl;
                          }
#line 1409 "parser.tab.cc"
    break;

  case 60: // statement_group: statement statement
#line 358 "parser.yy"
                                     {
                            yylhs.value.as < Node * > () = new Node("STATEMENT_GROUP", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Statement group1" << std::endl;
                          }
#line 1420 "parser.tab.cc"
    break;

  case 61: // statement_group: statement_group statement
#line 364 "parser.yy"
                                            {
                            yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Statement group2" << std::endl;
                          }
#line 1430 "parser.tab.cc"
    break;

  case 62: // statement_group: statement
#line 369 "parser.yy"
                            {
                            yylhs.value.as < Node * > () = new Node("STATEMENT_GROUP", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            std::cerr << "Statement group3" << std::endl;
                          }
#line 1440 "parser.tab.cc"
    break;

  case 63: // identifier: IDENTIFIER
#line 374 "parser.yy"
                       {  yylhs.value.as < Node * > () = new Node("Identifier", yystack_[0].value.as < std::string > (), yylineno); std::cerr << "Iden " << yystack_[0].value.as < std::string > () << std::endl;}
#line 1446 "parser.tab.cc"
    break;


#line 1450 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -23;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      -2,     5,    36,    29,   -23,   -22,   -23,   -23,   -22,   -23,
     -23,    37,    44,    40,    -1,    35,    19,    45,   -23,   -23,
     -23,   -23,   -22,    21,   -23,    65,   -22,    48,    66,   -23,
     -23,   -23,    84,    71,   -23,   -23,    72,    50,    98,    88,
     -22,    24,    86,     1,   -23,    91,    19,    87,    92,    94,
      99,   217,   157,   -23,   -23,   115,     8,   128,   -22,   -22,
     217,   217,   217,   -23,   -23,   -23,    14,   217,   217,   -23,
     279,   -23,   -23,   192,   172,     8,   217,   -23,   -23,   217,
     217,   217,   152,   -23,   100,   218,   235,   250,    95,   103,
       2,   265,   108,    17,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   -23,   -23,   -23,   293,   374,   307,
     321,   217,   111,   192,   192,   110,   217,   113,   -23,   -23,
     -23,   116,   386,    52,    52,     2,     2,   422,   422,   434,
     434,   434,   124,   114,   -23,   125,   335,   192,   141,   -23,
     -23,   398,   -23,   203,   -23,   -23,   217,   -23,   132,   178,
     192,   -23,   -23,   362,    62,   349,   -23,   134,   -23,   217,
     -23,   217,   -23,   -23,   410,   410
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     3,     0,     1,     2,     0,     4,
      63,     0,     0,     0,     0,     0,     0,    15,    14,     7,
      56,    57,     0,     0,    16,     0,     0,     0,     0,     6,
      58,    59,     0,     0,    13,     8,     0,     0,     0,     0,
       0,     0,     0,     0,    51,     0,     0,     0,     0,     0,
       0,     0,     0,    52,    53,     0,    16,     0,     0,     0,
       0,     0,     0,    39,    40,    42,     0,     0,     0,    38,
       0,    41,    17,    62,     0,     0,     0,    55,    54,     0,
       0,     0,     0,    50,     0,     0,     0,     0,     0,     0,
      45,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,    18,    61,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,    12,
      35,     0,     0,    30,    31,    32,    33,    25,    26,    27,
      28,    29,     0,     0,    23,     0,     0,     0,    20,    21,
      22,     0,    44,     0,    34,    11,     0,    10,     0,     0,
       0,    43,    37,    49,     0,     0,     9,     0,    19,     0,
      36,     0,    24,     5,    47,    48
  };

  const short
  parser::yypgoto_[] =
  {
     -23,   -23,   -23,   -23,   -23,   -10,   137,    30,    38,     3,
     -23,   -23,   104,   -23,    39,    -5
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     4,     9,    53,    21,    22,    54,    70,
     154,    41,    55,    23,    74,    71
  };

  const unsigned char
  parser::yytable_[] =
  {
      11,     1,    16,    12,    20,    17,    18,    17,    18,    24,
       5,    24,    48,    30,    49,    50,    51,    28,    24,    10,
      88,    33,    19,    52,    16,    17,    18,    17,    18,     7,
      93,    94,    24,   120,     8,    44,     6,    79,    56,    25,
      10,    24,    10,    15,    29,    77,    26,    75,    80,    45,
      56,    46,    56,    83,    84,    10,    17,    18,    10,    13,
      10,    89,    10,    85,    86,    87,    14,    40,    75,    75,
      90,    91,    77,    32,    27,    39,    58,    56,    34,   107,
      93,    94,   108,   109,   110,    97,    98,   160,   121,   161,
      73,    10,    35,    78,    36,    37,    38,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,    42,    75,    75,
      43,   104,   106,    57,   136,    47,    60,    59,    61,   141,
      78,    17,    18,    62,   116,   112,    48,   117,    49,    50,
      76,   119,    75,   137,    17,    18,   140,    52,   142,    48,
     143,    49,    50,    81,    75,    75,   153,   145,   147,   155,
      52,   138,   139,   150,   146,   156,    10,   163,    17,    18,
      31,    82,   164,    48,   165,    49,    50,   111,    48,    10,
      49,    50,     0,     0,    52,    73,   149,     0,     0,    52,
      72,     0,     0,    48,     0,    49,    50,   106,   158,    48,
       0,    49,    50,    10,    52,   105,     0,     0,    10,     0,
      52,   157,     0,    48,     0,    49,    50,     0,     0,     0,
       0,     0,     0,    10,    52,     0,     0,     0,     0,    10,
      63,    64,    65,    66,    67,     0,     0,    68,   152,     0,
       0,     0,     0,    10,    63,    64,    65,    66,    67,     0,
       0,    68,     0,   113,    10,    69,    93,    94,     0,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    10,    69,
     114,     0,     0,    93,    94,     0,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   115,     0,     0,    93,    94,
       0,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     118,     0,     0,    93,    94,     0,    95,    96,    97,    98,
      99,   100,   101,   102,   103,    92,     0,    93,    94,     0,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   132,
       0,    93,    94,     0,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   134,     0,    93,    94,     0,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   135,     0,    93,
      94,     0,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   148,     0,    93,    94,     0,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   162,     0,    93,    94,     0,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   159,
      93,    94,     0,    95,    96,    97,    98,    99,   100,   101,
     102,   103,    93,    94,   133,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    93,    94,   144,    95,    96,    97,
      98,    99,   100,   101,   102,   103,    93,    94,   151,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    93,    94,
       0,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      93,    94,     0,    95,    96,    97,    98,     0,     0,   101,
     102,   103,    93,    94,     0,    95,    96,    97,    98
  };

  const short
  parser::yycheck_[] =
  {
       5,     3,     3,     8,    14,     6,     7,     6,     7,    14,
       5,    16,    11,    23,    13,    14,    15,    22,    23,    41,
       6,    26,    23,    22,     3,     6,     7,     6,     7,     0,
      28,    29,    37,    16,     5,    40,     0,    29,    43,     4,
      41,    46,    41,     3,    23,    55,    16,    52,    40,    25,
      55,    27,    57,    58,    59,    41,     6,     7,    41,    22,
      41,    66,    41,    60,    61,    62,    22,    37,    73,    74,
      67,    68,    82,     8,    29,    25,    46,    82,    30,    76,
      28,    29,    79,    80,    81,    33,    34,    25,    93,    27,
      52,    41,    26,    55,    10,    24,    24,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,     9,   113,   114,
      22,    73,    74,    22,   111,    29,    24,    30,    24,   116,
      82,     6,     7,    24,    29,    25,    11,    24,    13,    14,
      15,    23,   137,    22,     6,     7,    26,    22,    25,    11,
      24,    13,    14,    15,   149,   150,   143,    23,    23,   146,
      22,   113,   114,    12,    40,    23,    41,    23,     6,     7,
      23,    57,   159,    11,   161,    13,    14,    15,    11,    41,
      13,    14,    -1,    -1,    22,   137,   137,    -1,    -1,    22,
      23,    -1,    -1,    11,    -1,    13,    14,   149,   150,    11,
      -1,    13,    14,    41,    22,    23,    -1,    -1,    41,    -1,
      22,    23,    -1,    11,    -1,    13,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    22,    -1,    -1,    -1,    -1,    41,
      17,    18,    19,    20,    21,    -1,    -1,    24,    25,    -1,
      -1,    -1,    -1,    41,    17,    18,    19,    20,    21,    -1,
      -1,    24,    -1,    25,    41,    42,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    41,    42,
      25,    -1,    -1,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    25,    -1,    -1,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      25,    -1,    -1,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    26,    -1,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    26,
      -1,    28,    29,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    26,    -1,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    26,    -1,    28,
      29,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    26,    -1,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    26,    -1,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      28,    29,    -1,    31,    32,    33,    34,    -1,    -1,    37,
      38,    39,    28,    29,    -1,    31,    32,    33,    34
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,    45,    46,    47,     5,     0,     0,     5,    48,
      41,    59,    59,    22,    22,     3,     3,     6,     7,    23,
      49,    50,    51,    57,    59,     4,    51,    29,    59,    23,
      49,    50,     8,    59,    30,    26,    10,    24,    24,    25,
      51,    55,     9,    22,    59,    25,    27,    29,    11,    13,
      14,    15,    22,    49,    52,    56,    59,    22,    51,    30,
      24,    24,    24,    17,    18,    19,    20,    21,    24,    42,
      53,    59,    23,    52,    58,    59,    15,    49,    52,    29,
      40,    15,    56,    59,    59,    53,    53,    53,     6,    59,
      53,    53,    26,    28,    29,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    52,    23,    52,    53,    53,    53,
      53,    15,    25,    25,    25,    25,    29,    24,    25,    23,
      16,    59,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    26,    30,    26,    26,    53,    22,    52,    52,
      26,    53,    25,    24,    30,    23,    40,    23,    26,    58,
      12,    30,    25,    53,    54,    53,    23,    23,    52,    27,
      25,    27,    26,    23,    53,    53
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    44,    45,    46,    46,    47,    48,    48,    49,    50,
      50,    50,    50,    51,    51,    51,    51,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    54,    54,    54,
      55,    55,    56,    56,    56,    56,    57,    57,    57,    57,
      58,    58,    58,    59
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     1,     2,    18,     5,     4,     3,    12,
      11,    11,    10,     3,     1,     1,     1,     2,     3,     7,
       5,     5,     5,     4,     7,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     3,     6,     5,     1,     1,
       1,     1,     1,     5,     4,     2,     3,     3,     3,     1,
       4,     2,     1,     1,     2,     2,     1,     1,     2,     2,
       2,     2,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "PUBLIC", "STATIC",
  "CLASS", "TYPE_INT", "TYPE_BOOLEAN", "VOID", "STRING", "MAIN", "IF",
  "ELSE", "WHILE", "PRINT", "RETURN", "LENGTH", "TRUE", "FALSE", "THIS",
  "NEW", "NOT", "OPEN_BRACE", "CLOSE_BRACE", "OPEN_PAREN", "CLOSE_PAREN",
  "SEMICOLON", "COMMA", "DOT", "OPEN_BRACKET", "CLOSE_BRACKET", "PLUS",
  "MINUS", "MULTIPLY", "DIVIDE", "AND", "OR", "LESS_THAN", "GREATER_THAN",
  "EQUAL", "ASSIGN", "IDENTIFIER", "INTEGER_LITERAL", "WS", "$accept",
  "root", "goal", "main_class", "class_declaration", "var_declaration",
  "method_declaration", "type", "statement", "expression",
  "expression_parameter", "identifier_parameter", "method_body",
  "class_body", "statement_group", "identifier", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    36,    36,    37,    41,    48,    58,    64,    70,    77,
      90,   102,   114,   126,   130,   134,   137,   143,   145,   147,
     154,   160,   166,   171,   177,   187,   193,   199,   205,   211,
     217,   223,   229,   235,   241,   247,   253,   259,   264,   265,
     266,   267,   268,   269,   274,   279,   284,   287,   293,   298,
     300,   308,   317,   322,   327,   332,   338,   343,   348,   353,
     358,   364,   369,   374
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2074 "parser.tab.cc"


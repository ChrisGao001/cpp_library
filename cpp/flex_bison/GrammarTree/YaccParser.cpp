// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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


// First part of user declarations.

#line 37 "YaccParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "YaccParser.h"

// User implementation prologue.

#line 51 "YaccParser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 35 "ba.yy" // lalr1.cc:413

    #include "YaccDriver.h"

#line 57 "YaccParser.cpp" // lalr1.cc:413


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

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

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
      *yycdebug_ << std::endl;                  \
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
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 10 "ba.yy" // lalr1.cc:479
namespace BA {
#line 143 "YaccParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  YaccParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
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
              // Fall through.
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


  /// Build a parser object.
  YaccParser::YaccParser (YaccDriver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  YaccParser::~YaccParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  YaccParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  YaccParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  YaccParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  YaccParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  YaccParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  YaccParser::symbol_number_type
  YaccParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  YaccParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  YaccParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 43: // LimitRange
        value.move<  std::vector<int>  > (that.value);
        break;

      case 39: // AllModule
        value.move< AllModule* > (that.value);
        break;

      case 44: // AuxAssign
        value.move< AuxAssign* > (that.value);
        break;

      case 46: // Condition
        value.move< Condition* > (that.value);
        break;

      case 45: // ConditionExpr
        value.move< ConditionExpr* > (that.value);
        break;

      case 38: // HcCidModule
        value.move< HcCidModule* > (that.value);
        break;

      case 12: // KEYWORD
        value.move< KeyWord > (that.value);
        break;

      case 36: // Module
        value.move< Module* > (that.value);
        break;

      case 35: // Modules
        value.move< Modules* > (that.value);
        break;

      case 37: // QueryModule
        value.move< QueryModule* > (that.value);
        break;

      case 41: // Stmt
        value.move< Stmt* > (that.value);
        break;

      case 40: // Stmts
        value.move< Stmts* > (that.value);
        break;

      case 42: // WhenStmt
        value.move< WhenStmt* > (that.value);
        break;

      case 10: // DOUBLE
        value.move< double > (that.value);
        break;

      case 47: // AuxAssignOp
      case 48: // CompOp
        value.move< int > (that.value);
        break;

      case 11: // INTEGER
      case 49: // Integer
        value.move< int64_t > (that.value);
        break;

      case 8: // IDENT
      case 9: // STRING
      case 50: // String
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  YaccParser::stack_symbol_type&
  YaccParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 43: // LimitRange
        value.copy<  std::vector<int>  > (that.value);
        break;

      case 39: // AllModule
        value.copy< AllModule* > (that.value);
        break;

      case 44: // AuxAssign
        value.copy< AuxAssign* > (that.value);
        break;

      case 46: // Condition
        value.copy< Condition* > (that.value);
        break;

      case 45: // ConditionExpr
        value.copy< ConditionExpr* > (that.value);
        break;

      case 38: // HcCidModule
        value.copy< HcCidModule* > (that.value);
        break;

      case 12: // KEYWORD
        value.copy< KeyWord > (that.value);
        break;

      case 36: // Module
        value.copy< Module* > (that.value);
        break;

      case 35: // Modules
        value.copy< Modules* > (that.value);
        break;

      case 37: // QueryModule
        value.copy< QueryModule* > (that.value);
        break;

      case 41: // Stmt
        value.copy< Stmt* > (that.value);
        break;

      case 40: // Stmts
        value.copy< Stmts* > (that.value);
        break;

      case 42: // WhenStmt
        value.copy< WhenStmt* > (that.value);
        break;

      case 10: // DOUBLE
        value.copy< double > (that.value);
        break;

      case 47: // AuxAssignOp
      case 48: // CompOp
        value.copy< int > (that.value);
        break;

      case 11: // INTEGER
      case 49: // Integer
        value.copy< int64_t > (that.value);
        break;

      case 8: // IDENT
      case 9: // STRING
      case 50: // String
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  YaccParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  YaccParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  YaccParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  YaccParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  YaccParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  YaccParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  YaccParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  YaccParser::debug_level_type
  YaccParser::debug_level () const
  {
    return yydebug_;
  }

  void
  YaccParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline YaccParser::state_type
  YaccParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  YaccParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  YaccParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  YaccParser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 28 "ba.yy" // lalr1.cc:741
{
    // Initialize the initial location.
    yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 561 "YaccParser.cpp" // lalr1.cc:741

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

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
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 43: // LimitRange
        yylhs.value.build<  std::vector<int>  > ();
        break;

      case 39: // AllModule
        yylhs.value.build< AllModule* > ();
        break;

      case 44: // AuxAssign
        yylhs.value.build< AuxAssign* > ();
        break;

      case 46: // Condition
        yylhs.value.build< Condition* > ();
        break;

      case 45: // ConditionExpr
        yylhs.value.build< ConditionExpr* > ();
        break;

      case 38: // HcCidModule
        yylhs.value.build< HcCidModule* > ();
        break;

      case 12: // KEYWORD
        yylhs.value.build< KeyWord > ();
        break;

      case 36: // Module
        yylhs.value.build< Module* > ();
        break;

      case 35: // Modules
        yylhs.value.build< Modules* > ();
        break;

      case 37: // QueryModule
        yylhs.value.build< QueryModule* > ();
        break;

      case 41: // Stmt
        yylhs.value.build< Stmt* > ();
        break;

      case 40: // Stmts
        yylhs.value.build< Stmts* > ();
        break;

      case 42: // WhenStmt
        yylhs.value.build< WhenStmt* > ();
        break;

      case 10: // DOUBLE
        yylhs.value.build< double > ();
        break;

      case 47: // AuxAssignOp
      case 48: // CompOp
        yylhs.value.build< int > ();
        break;

      case 11: // INTEGER
      case 49: // Integer
        yylhs.value.build< int64_t > ();
        break;

      case 8: // IDENT
      case 9: // STRING
      case 50: // String
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 96 "ba.yy" // lalr1.cc:859
    {
                    if (yystack_[0].value.as< Modules* > ()) {
                        driver.root = driver.ReverseModuleList(yystack_[0].value.as< Modules* > ());
                        YYCDEBUG << "root:" << driver.root << std::endl;
                    } else {
                        driver.root = NULL;
                    }
                }
#line 750 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 104 "ba.yy" // lalr1.cc:859
    {driver.root = NULL;}
#line 756 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 106 "ba.yy" // lalr1.cc:859
    {
                    /*如果下一个匹配的Module为空则不重复构建*/
                    if (NULL == yystack_[0].value.as< Module* > ()) {
                        yylhs.value.as< Modules* > () = yystack_[1].value.as< Modules* > ();
                    } else {
                        yylhs.value.as< Modules* > () = new Modules(yystack_[1].value.as< Modules* > (),yystack_[0].value.as< Module* > ());
                        driver.BackupNode(yylhs.value.as< Modules* > ());
                    }
                }
#line 770 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 114 "ba.yy" // lalr1.cc:859
    {
                    if (yystack_[0].value.as< Module* > ()){
                        yylhs.value.as< Modules* > () = new Modules(NULL,yystack_[0].value.as< Module* > ());
                        driver.BackupNode(yylhs.value.as< Modules* > ());
                    } else {
                        yylhs.value.as< Modules* > () = NULL;
                    }
                }
#line 783 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 123 "ba.yy" // lalr1.cc:859
    {yylhs.value.as< Module* > () = yystack_[0].value.as< QueryModule* > ();}
#line 789 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 124 "ba.yy" // lalr1.cc:859
    {yylhs.value.as< Module* > () = yystack_[0].value.as< HcCidModule* > ();}
#line 795 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 125 "ba.yy" // lalr1.cc:859
    {yylhs.value.as< Module* > () = yystack_[0].value.as< AllModule* > ();}
#line 801 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 127 "ba.yy" // lalr1.cc:859
    {
                    if (yystack_[1].value.as< Stmts* > ()) {
                        yylhs.value.as< QueryModule* > () = new QueryModule(yystack_[3].value.as< std::string > (),driver.ReverseStmtsList(yystack_[1].value.as< Stmts* > ()));
                        driver.BackupNode(yylhs.value.as< QueryModule* > ());
                    } else {
                        yylhs.value.as< QueryModule* > () = NULL;
                    }
                }
#line 814 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 136 "ba.yy" // lalr1.cc:859
    {
                    if (yystack_[1].value.as< Stmts* > ()) {
                        yylhs.value.as< HcCidModule* > () = new HcCidModule(yystack_[3].value.as< int64_t > (),driver.ReverseStmtsList(yystack_[1].value.as< Stmts* > ()));
                        driver.BackupNode(yylhs.value.as< HcCidModule* > ());
                    } else {
                        yylhs.value.as< HcCidModule* > () = NULL;
                    }
                }
#line 827 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 145 "ba.yy" // lalr1.cc:859
    {
                    if (yystack_[1].value.as< Stmts* > ()) {
                        yylhs.value.as< AllModule* > () = new AllModule(driver.ReverseStmtsList(yystack_[1].value.as< Stmts* > ()));
                        driver.BackupNode(yylhs.value.as< AllModule* > ());
                    } else {
                        yylhs.value.as< AllModule* > () = NULL;
                    }
                }
#line 840 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 154 "ba.yy" // lalr1.cc:859
    {
                    if (NULL == yystack_[0].value.as< Stmt* > ()) {
                        /*如badcase:
                         * do position when price > 100;;;;;;
                         */
                        yylhs.value.as< Stmts* > () = yystack_[2].value.as< Stmts* > ();
                    } else {
                        yylhs.value.as< Stmts* > () = new Stmts(yystack_[2].value.as< Stmts* > (),yystack_[0].value.as< Stmt* > ());
                        driver.BackupNode(yylhs.value.as< Stmts* > ());
                    }
                }
#line 856 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 165 "ba.yy" // lalr1.cc:859
    {
                    if (yystack_[0].value.as< Stmt* > ()) {
                        yylhs.value.as< Stmts* > () = new Stmts(NULL,yystack_[0].value.as< Stmt* > ());
                        driver.BackupNode(yylhs.value.as< Stmts* > ());
                    } else {
                        yylhs.value.as< Stmts* > () = NULL;
                    }
                }
#line 869 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 174 "ba.yy" // lalr1.cc:859
    {yylhs.value.as< Stmt* > () = yystack_[0].value.as< WhenStmt* > ();}
#line 875 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 175 "ba.yy" // lalr1.cc:859
    {yylhs.value.as< Stmt* > () = NULL;}
#line 881 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 177 "ba.yy" // lalr1.cc:859
    {
                    std::vector<int> vec;
                    yylhs.value.as< WhenStmt* > () = new WhenStmt(yystack_[2].value.as< AuxAssign* > (),yystack_[0].value.as< ConditionExpr* > (),vec,"");
                    driver.BackupNode(yylhs.value.as< WhenStmt* > ());
                }
#line 891 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 183 "ba.yy" // lalr1.cc:859
    {
                    yylhs.value.as< WhenStmt* > () = new WhenStmt(yystack_[3].value.as< AuxAssign* > (),yystack_[1].value.as< ConditionExpr* > (),yystack_[0].value.as<  std::vector<int>  > (),"");
                    driver.BackupNode(yylhs.value.as< WhenStmt* > ());
                }
#line 900 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 188 "ba.yy" // lalr1.cc:859
    {
                    yylhs.value.as< WhenStmt* > () = new WhenStmt(yystack_[5].value.as< AuxAssign* > (),yystack_[3].value.as< ConditionExpr* > (),yystack_[2].value.as<  std::vector<int>  > (),yystack_[0].value.as< std::string > ());
                    driver.BackupNode(yylhs.value.as< WhenStmt* > ());
                }
#line 909 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 193 "ba.yy" // lalr1.cc:859
    {
                    std::vector<int> vec;
                    yylhs.value.as< WhenStmt* > () = new WhenStmt(yystack_[4].value.as< AuxAssign* > (),yystack_[2].value.as< ConditionExpr* > (),vec,yystack_[0].value.as< std::string > ());
                    driver.BackupNode(yylhs.value.as< WhenStmt* > ());
                }
#line 919 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 200 "ba.yy" // lalr1.cc:859
    {
                    std::vector<int> vec;
                    vec.push_back(yystack_[0].value.as< int64_t > ());
                    yylhs.value.as<  std::vector<int>  > () = vec;
                }
#line 929 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 206 "ba.yy" // lalr1.cc:859
    {
                    std::vector<int> vec;
                    vec.push_back(yystack_[2].value.as< int64_t > ());
                    vec.push_back(yystack_[0].value.as< int64_t > ());
                    yylhs.value.as<  std::vector<int>  > () = vec;
                }
#line 940 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 213 "ba.yy" // lalr1.cc:859
    {
                    yylhs.value.as< AuxAssign* > () = new AuxAssign(yystack_[2].value.as< KeyWord > (),yystack_[1].value.as< int > (),yystack_[0].value.as< int64_t > ());
                    driver.BackupNode(yylhs.value.as< AuxAssign* > ());
                }
#line 949 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 218 "ba.yy" // lalr1.cc:859
    {
                    yylhs.value.as< ConditionExpr* > () = new ConditionExpr(yystack_[2].value.as< ConditionExpr* > (),yystack_[0].value.as< Condition* > ());
                    driver.BackupNode(yylhs.value.as< ConditionExpr* > ());
                }
#line 958 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 222 "ba.yy" // lalr1.cc:859
    {
                    yylhs.value.as< ConditionExpr* > () = new ConditionExpr(yystack_[0].value.as< Condition* > ());
                    driver.BackupNode(yylhs.value.as< ConditionExpr* > ());
                }
#line 967 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 227 "ba.yy" // lalr1.cc:859
    {
                    yylhs.value.as< Condition* > () = new Condition(yystack_[2].value.as< KeyWord > (),yystack_[1].value.as< int > (),yystack_[0].value.as< int64_t > ());
                    driver.BackupNode(yylhs.value.as< Condition* > ());
                }
#line 976 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 232 "ba.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = ADD_ASSIGN; }
#line 982 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 233 "ba.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = SUB_ASSIGN; }
#line 988 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 234 "ba.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = MUL_ASSIGN; }
#line 994 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 235 "ba.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = ASSIGN; }
#line 1000 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 237 "ba.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = LE_OP; }
#line 1006 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 238 "ba.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = GE_OP; }
#line 1012 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 239 "ba.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = EQ_OP; }
#line 1018 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 240 "ba.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = NE_OP; }
#line 1024 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 241 "ba.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = LT_OP; }
#line 1030 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 242 "ba.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = GT_OP; }
#line 1036 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 244 "ba.yy" // lalr1.cc:859
    { yylhs.value.as< int64_t > () = (int64_t)yystack_[0].value.as< int64_t > (); }
#line 1042 "YaccParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 246 "ba.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1048 "YaccParser.cpp" // lalr1.cc:859
    break;


#line 1052 "YaccParser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  YaccParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  YaccParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

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
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char YaccParser::yypact_ninf_ = -51;

  const signed char YaccParser::yytable_ninf_ = -1;

  const signed char
  YaccParser::yypact_[] =
  {
      -5,    -3,     3,     4,    33,    -5,   -51,   -51,   -51,   -51,
     -51,    16,   -51,    17,    34,   -51,   -51,    34,    34,    24,
      -8,   -51,   -51,     8,    10,   -21,    35,   -51,    34,   -51,
     -51,   -51,   -51,   -51,   -51,     3,    26,   -51,   -51,   -11,
      19,   -51,   -51,   -51,   -51,   -51,   -51,   -51,     3,    26,
       3,    -3,    36,   -51,   -51,    20,   -51,    -3,     3,   -51,
     -51
  };

  const unsigned char
  YaccParser::yydefact_[] =
  {
       3,     0,     0,     0,     0,     2,     5,     6,     7,     8,
      37,     0,    36,     0,    15,     1,     4,    15,    15,     0,
       0,    13,    14,     0,     0,     0,     0,    11,    15,     9,
      10,    26,    27,    28,    29,     0,     0,    12,    22,     0,
      16,    24,    30,    31,    32,    33,    34,    35,     0,     0,
       0,     0,    17,    25,    23,    20,    19,     0,     0,    18,
      21
  };

  const signed char
  YaccParser::yypgoto_[] =
  {
     -51,   -51,   -51,    37,   -51,   -51,   -51,    14,    12,   -51,
     -51,   -51,   -51,    -4,   -51,   -51,   -35,   -50
  };

  const signed char
  YaccParser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,     8,     9,    20,    21,    22,
      52,    26,    40,    41,    35,    48,    13,    11
  };

  const unsigned char
  YaccParser::yytable_[] =
  {
      38,    56,    31,    32,    33,    34,    10,    59,     1,     2,
       3,    27,    28,    53,    12,    55,    42,    43,    44,    45,
      46,    47,    14,    60,    49,    50,    51,    29,    28,    30,
      28,    23,    24,    15,    17,    18,    25,    19,    39,    36,
      37,    58,    16,    57,     0,    54
  };

  const signed char
  YaccParser::yycheck_[] =
  {
      35,    51,    23,    24,    25,    26,     9,    57,    13,    14,
      15,    19,    20,    48,    11,    50,    27,    28,    29,    30,
      31,    32,    18,    58,     5,     6,     7,    19,    20,    19,
      20,    17,    18,     0,    18,    18,    12,     3,    12,     4,
      28,    21,     5,     7,    -1,    49
  };

  const unsigned char
  YaccParser::yystos_[] =
  {
       0,    13,    14,    15,    34,    35,    36,    37,    38,    39,
       9,    50,    11,    49,    18,     0,    36,    18,    18,     3,
      40,    41,    42,    40,    40,    12,    44,    19,    20,    19,
      19,    23,    24,    25,    26,    47,     4,    41,    49,    12,
      45,    46,    27,    28,    29,    30,    31,    32,    48,     5,
       6,     7,    43,    49,    46,    49,    50,     7,    21,    50,
      49
  };

  const unsigned char
  YaccParser::yyr1_[] =
  {
       0,    33,    34,    34,    35,    35,    36,    36,    36,    37,
      38,    39,    40,    40,    41,    41,    42,    42,    42,    42,
      43,    43,    44,    45,    45,    46,    47,    47,    47,    47,
      48,    48,    48,    48,    48,    48,    49,    50
  };

  const unsigned char
  YaccParser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     1,     1,     1,     1,     5,
       5,     4,     3,     1,     1,     0,     4,     5,     7,     6,
       2,     4,     3,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const YaccParser::yytname_[] =
  {
  "END", "error", "$undefined", "DO", "WHEN", "AND", "LIMIT", "MTEST",
  "IDENT", "STRING", "DOUBLE", "INTEGER", "KEYWORD", "QUERY", "HC_CID",
  "ALL", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "SEMICOLON", "COMMA",
  "TOC_UNKNOWN", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "ASSIGN",
  "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "LT_OP", "GT_OP", "$accept", "Input",
  "Modules", "Module", "QueryModule", "HcCidModule", "AllModule", "Stmts",
  "Stmt", "WhenStmt", "LimitRange", "AuxAssign", "ConditionExpr",
  "Condition", "AuxAssignOp", "CompOp", "Integer", "String", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  YaccParser::yyrline_[] =
  {
       0,    96,    96,   104,   106,   114,   123,   124,   125,   127,
     136,   145,   154,   165,   174,   175,   177,   182,   187,   192,
     199,   205,   213,   218,   222,   227,   232,   233,   234,   235,
     237,   238,   239,   240,   241,   242,   244,   246
  };

  // Print the state stack on the debug stream.
  void
  YaccParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  YaccParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 10 "ba.yy" // lalr1.cc:1167
} // BA
#line 1458 "YaccParser.cpp" // lalr1.cc:1167
#line 247 "ba.yy" // lalr1.cc:1168


void BA::YaccParser::error (const location_type& l, const std::string& m)
{
    driver.Error (l, m);
}


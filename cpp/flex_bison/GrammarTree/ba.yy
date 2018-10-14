%skeleton "lalr1.cc" /* -*- C++ -*- bison version 2.4.1 */
%require "3.0.4"
%defines "YaccParser.h"
%output "YaccParser.cpp"

%define parser_class_name {YaccParser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace {BA}

%code requires
{
#include <string>
#include <assert.h>
#include "Node.h"

namespace BA {
class YaccDriver;
} /*namespace BA*/

}

// The parsing context.
%param { YaccDriver& driver }
%locations
%initial-action
{
    // Initialize the initial location.
    @$.begin.filename = @$.end.filename = &driver.file;
};
%define parse.trace
%define parse.error verbose
%code
{
    #include "YaccDriver.h"
}
%define api.token.prefix {TOK_}

/*keyword token*/
%token DO WHEN AND LIMIT MTEST
%token <std::string> IDENT
%token <std::string> STRING
%token <double>   DOUBLE
%token <int64_t>      INTEGER
%token <KeyWord>  KEYWORD

%token QUERY
%token HC_CID
%token ALL

%token LPAREN
       RPAREN
       LBRACE
       RBRACE
       SEMICOLON
       COMMA
       TOC_UNKNOWN

%token ADD_ASSIGN
       SUB_ASSIGN
       MUL_ASSIGN
       ASSIGN

%token LE_OP
       GE_OP
       EQ_OP
       NE_OP
       LT_OP
       GT_OP

%token END 0

%type <Modules*> Modules
%type <Module*> Module
%type <QueryModule*> QueryModule
%type <HcCidModule*> HcCidModule
%type <AllModule*> AllModule

%type <Stmt*> Stmt
%type <Stmts*> Stmts
%type <WhenStmt*> WhenStmt
%type <ConditionExpr*> ConditionExpr

%type <AuxAssign*> AuxAssign
%type <Condition*> Condition
%type < std::vector<int> > LimitRange

%type <int64_t> Integer
%type <std::string> String
%type <int> AuxAssignOp CompOp

%%

%start Input;
Input           : Modules {
                    if ($1) {
                        driver.root = driver.ReverseModuleList($1);
                        YYCDEBUG << "root:" << driver.root << std::endl;
                    } else {
                        driver.root = NULL;
                    }
                }
                | /*EMPTY*/  {driver.root = NULL;} ;

Modules         : Modules Module {
                    /*如果下一个匹配的Module为空则不重复构建*/
                    if (NULL == $2) {
                        $$ = $1;
                    } else {
                        $$ = new Modules($1,$2);
                        driver.BackupNode($$);
                    }
                } | Module {
                    if ($1){
                        $$ = new Modules(NULL,$1);
                        driver.BackupNode($$);
                    } else {
                        $$ = NULL;
                    }
                } ;

Module          : QueryModule {$$ = $1;}
                | HcCidModule {$$ = $1;}
                | AllModule {$$ = $1;} ;

QueryModule     : QUERY String LBRACE Stmts RBRACE {
                    if ($4) {
                        $$ = new QueryModule($2,driver.ReverseStmtsList($4));
                        driver.BackupNode($$);
                    } else {
                        $$ = NULL;
                    }
                } ;

HcCidModule     : HC_CID Integer LBRACE Stmts RBRACE {
                    if ($4) {
                        $$ = new HcCidModule($2,driver.ReverseStmtsList($4));
                        driver.BackupNode($$);
                    } else {
                        $$ = NULL;
                    }
                } ;

AllModule       : ALL LBRACE Stmts RBRACE {
                    if ($3) {
                        $$ = new AllModule(driver.ReverseStmtsList($3));
                        driver.BackupNode($$);
                    } else {
                        $$ = NULL;
                    }
                } ;

Stmts           : Stmts SEMICOLON Stmt {
                    if (NULL == $3) {
                        /*如badcase:
                         * do position when price > 100;;;;;;
                         */
                        $$ = $1;
                    } else {
                        $$ = new Stmts($1,$3);
                        driver.BackupNode($$);
                    }
                }
                | Stmt {
                    if ($1) {
                        $$ = new Stmts(NULL,$1);
                        driver.BackupNode($$);
                    } else {
                        $$ = NULL;
                    }
                } ;

Stmt            : WhenStmt      {$$ = $1;}
                | /*EMPTY*/     {$$ = NULL;} ;

WhenStmt        : DO AuxAssign WHEN ConditionExpr {
                    std::vector<int> vec;
                    $$ = new WhenStmt($2,$4,vec,"");
                    driver.BackupNode($$);
                }
                | DO AuxAssign WHEN ConditionExpr LimitRange
                {
                    $$ = new WhenStmt($2,$4,$5,"");
                    driver.BackupNode($$);
                }
                | DO AuxAssign WHEN ConditionExpr LimitRange MTEST String
                {
                    $$ = new WhenStmt($2,$4,$5,$7);
                    driver.BackupNode($$);
                }
                | DO AuxAssign WHEN ConditionExpr MTEST String
                {
                    std::vector<int> vec;
                    $$ = new WhenStmt($2,$4,vec,$6);
                    driver.BackupNode($$);
                }
                ;
LimitRange      : LIMIT Integer
                {
                    std::vector<int> vec;
                    vec.push_back($2);
                    $$ = vec;
                }
                | LIMIT Integer COMMA Integer
                {
                    std::vector<int> vec;
                    vec.push_back($2);
                    vec.push_back($4);
                    $$ = vec;
                };

AuxAssign       : KEYWORD AuxAssignOp Integer {
                    $$ = new AuxAssign($1,$2,$3);
                    driver.BackupNode($$);
                } ;

ConditionExpr   : ConditionExpr AND Condition {
                    $$ = new ConditionExpr($1,$3);
                    driver.BackupNode($$);
                }
                | Condition {
                    $$ = new ConditionExpr($1);
                    driver.BackupNode($$);
                } ;

Condition       : KEYWORD CompOp Integer {
                    $$ = new Condition($1,$2,$3);
                    driver.BackupNode($$);
                } ;

AuxAssignOp     : ADD_ASSIGN { $$ = ADD_ASSIGN; }
                | SUB_ASSIGN { $$ = SUB_ASSIGN; }
                | MUL_ASSIGN { $$ = MUL_ASSIGN; }
                | ASSIGN { $$ = ASSIGN; } ;

CompOp          : LE_OP { $$ = LE_OP; }
                | GE_OP { $$ = GE_OP; }
                | EQ_OP { $$ = EQ_OP; }
                | NE_OP { $$ = NE_OP; }
                | LT_OP { $$ = LT_OP; }
                | GT_OP { $$ = GT_OP; } ;

Integer         : INTEGER { $$ = (int64_t)$1; } ;

String          : STRING { $$ = $1; } ;
%%

void BA::YaccParser::error (const location_type& l, const std::string& m)
{
    driver.Error (l, m);
}


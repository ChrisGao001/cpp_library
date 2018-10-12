#include "Node.h"

#include <iostream>
#include <boost/lexical_cast.hpp>

namespace BA {

Node::Node()
{
}

Node::~Node()
{
}

Modules::Modules(Modules* modules,Module* module)
    : modules(modules),
      module(module)
{
}

Modules::~Modules()
{
}

Module::Module()
{
}

Module::~Module()
{
}

QueryModule::QueryModule(std::string& query,Stmts* stmts)
    : query(query),
      stmts(stmts)
{
}

QueryModule::~QueryModule()
{
}

HcCidModule::HcCidModule(int cid,Stmts* stmts)
    : cid(cid),
      stmts(stmts)
{
}

HcCidModule::~HcCidModule()
{
}

AllModule::AllModule(Stmts* stmts)
    : stmts(stmts)
{
}

AllModule::~AllModule()
{
}

Stmts::Stmts(Stmts* stmts,Stmt* stmt)
        : stmts(stmts),
          stmt(stmt)
{
}

Stmts::~Stmts()
{
}

Stmt::Stmt(AuxAssign* action_stmt,
            ConditionExpr* cond_expr,
            const std::vector<int>& bound,
            const std::string& mtest)
    : aux_assign(action_stmt)
    , cond_expr(cond_expr)
    , mtest(mtest)
{
    // [lower_bound,upper_bound]
    if (bound.size() == 1)
    {
        // only upper bound
        limit_bound.push_back(0);
        limit_bound.push_back(bound[0]);
    }
    else if (bound.size() == 2)
    {
        limit_bound = bound;
    }
    // else limit bound empty
}

Stmt::~Stmt()
{
}

WhenStmt::WhenStmt(AuxAssign* action_stmt,
            ConditionExpr* cond_expr,
            const std::vector<int>& limit_bound,
            const std::string& mtest)
        : Stmt(action_stmt,cond_expr,limit_bound,mtest)
{
}

WhenStmt::~WhenStmt()
{
}

AuxAssign::AuxAssign(KeyWord keyword,int assign_type,int number)
    : keyword(keyword),
      assign_type(assign_type),
      number(number)
{
}

AuxAssign::~AuxAssign()
{
}

ConditionExpr::ConditionExpr(ConditionExpr* expr,Condition* cond)
        : expr(expr),
          cond(cond)
{
}

ConditionExpr::ConditionExpr(Condition* cond)
        : expr(NULL),
          cond(cond)
{
}

ConditionExpr::~ConditionExpr()
{
}

Condition::Condition(KeyWord keyword,int op,int64_t num)
    : keyword(keyword),
      op(op),
      num(num)
{
}

Condition::~Condition()
{
}

} /*namespace BA*/

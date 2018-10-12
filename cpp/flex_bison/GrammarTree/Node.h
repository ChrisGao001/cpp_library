#ifndef __Node_H__
#define __Node_H__

#include <string>
#include <vector>
#include <stdint.h>

using std::string;

namespace BA {

class Node;

class Modules;
class Module;
class QueryModule;
class HcCidModule;
class AllModule;

class Stmt;
class Stmts;
class ConditionExpr;

class ActionStmt;
class AuxAssign;
class Condition;

enum AuxAssignType
{
    ADD_ASSIGN,
    SUB_ASSIGN,
    MUL_ASSIGN,
    ASSIGN,
};

enum OpType
{
    EQ_OP,
    NE_OP,
    GE_OP,
    LE_OP,
    GT_OP,
    LT_OP,
    NONE_OP,
};

enum KeyWord
{
    //正排字段
    KW_NONE = 0,
    KW_WAREID = 1,
    KW_WAREPID = 2,
    KW_BRAND_ID = 3,
    KW_CID3 = 4,
    KW_CID2 = 5,
    KW_CID1 = 6,
    KW_SHOP_ID = 7,
    KW_PRODUCTEXT = 8,
    KW_XREDISPRICE = 9,

    //避免与正排字段冲突
    KW_POSITION = 15,           //商品的位置
    KW_FLAGS = 16,              //商品的flags，用以判断是否京东自营，是否有货
    KW_BEGIN_DATE = 17,         //用以自动使规则失效
    KW_EXPIRE_DATE = 18,        //用以自动使规则失效
    KW_CHANNEL = 19,            //流量来源，是pc还是mobile
    KW_RANK_FLAGS = 20,         //是Rank模块打标的flags，用以配合其它排序模块调权
    KW_GOOD = 21,               //好评度

    // 需要额外读取的正排类型
    KW_NEED_RD_DOC = 30,

    KW_COUNT,
};

class Node
{
public:
    Node();
    virtual ~Node() = 0;
private:
};

class Modules
    : public Node
{
public:
    Modules(Modules* modules,Module* module);
    ~Modules();

public:
    Modules* modules;
    Module* module;
};

class Module
    : public Node
{
public:
    Module();
    ~Module();
};

class QueryModule
    : public Module
{
public:
    QueryModule(std::string& query,Stmts* stmts);
    ~QueryModule();

public:
    std::string query;
    Stmts* stmts;
};

class HcCidModule
    : public Module
{
public:
    HcCidModule(int cid,Stmts* stmts);
    ~HcCidModule();

public:
    int cid;
    Stmts* stmts;
};

class AllModule
    : public Module
{
public:
    AllModule(Stmts* stmts);
    ~AllModule();

public:
    Stmts* stmts;
};

class Stmts
    : public Node
{
public:
    Stmts(Stmts* stmts,Stmt* stmt);
    virtual ~Stmts();
public:
    Stmts* stmts;
    Stmt* stmt;
};

class Stmt
    : public Node
{
public:
    Stmt(AuxAssign* action_stmt,
            ConditionExpr* cond_expr,
            const std::vector<int>& limit_bound,
            const std::string& mtest);
    virtual ~Stmt() = 0;

public:
    AuxAssign* aux_assign;
    ConditionExpr* cond_expr;
    std::vector<int> limit_bound;
    std::string mtest;
};

class WhenStmt
    : public Stmt
{
public:
    WhenStmt(AuxAssign* action_stmt,
            ConditionExpr* cond_expr,
            const std::vector<int>& limit_bound,
            const std::string& mtest);

    virtual ~WhenStmt();

public:
};

class AuxAssign
    : public Node
{
public:
    AuxAssign(KeyWord keyword,int assign_type,int number);
    virtual ~AuxAssign();
public:
    KeyWord keyword;
    int assign_type;
    int number;
};

class ConditionExpr
    : public Node
{
public:
    ConditionExpr(ConditionExpr* expr,Condition* cond);
    ConditionExpr(Condition* cond);
    virtual ~ConditionExpr();

public:
    ConditionExpr* expr;
    Condition* cond;
};

class Condition
    : public Node
{
public:
    Condition(KeyWord keyword,int op,int64_t num);
    virtual ~Condition();
public:
    KeyWord keyword;
    int op;
    int64_t num;

    // add for doc reader
    bool b_multi_value;           // 是否多值
    int n_vlaue_type;           // 值类型
    int n_offset;               // 新flag标记位置 1-32 or 1-64
    std::string str_flag_name;  // 新flag变量名 
    std::string str_field_name; // 字段字符串

protected:
};

} /*namespace BA*/

#endif /*!__Node_H__*/

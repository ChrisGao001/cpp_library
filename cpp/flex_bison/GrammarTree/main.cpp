#include <map>
#include <vector>

#include "YaccDriver.h"

using namespace std;
using namespace BA;

struct StmtsNormalized
{
    std::map<int64_t,BA::Stmt*> WareidStmt;   //条件为wareid的规则
    std::vector<BA::Stmt*> MultiSelectStmt;   //可选出多个的规则
};

using namespace BA; 

int64_t find_condition_wareid( const BA::ConditionExpr* cond_expr)
{
    while (cond_expr)
    {
        if (cond_expr->cond)
        {
            BA::KeyWord keyword = cond_expr->cond->keyword;

            if (BA::KW_WAREID == keyword)
            {
                return cond_expr->cond->num;
            }
        }
        cond_expr = cond_expr->expr;
    }

    return 0;
}

void _NormalizeStmts(const Stmts* stmts,StmtsNormalized& inner)
{
    inner.WareidStmt.clear();
    inner.MultiSelectStmt.clear();

    while (stmts)
    {
        Stmt* stmt = stmts->stmt;
        if (stmt && stmt->cond_expr)
        {
            int64_t wareid = find_condition_wareid(stmt->cond_expr);
			cout <<"wareid " << wareid << endl;
            if (wareid)
            {
                inner.WareidStmt[wareid] = stmt;
            }
            else
            {
                inner.MultiSelectStmt.push_back(stmt);
            }
        }

        stmts = stmts->stmts;
    }

    return;
}

void WalkModule(Modules* mods, map<string,StmtsNormalized> &_query_stmts) {
	if (mods == NULL) {
		return;
	}
    while (mods) {
        Module* mod = mods->module;
        if (mod) {
            //注意这里一个规则，当同一种Module被多次定义之后，使用最后定义的一个
            QueryModule *query_module = dynamic_cast<QueryModule *>(mod);
            if (query_module) {
                if (not query_module->query.empty() && query_module->stmts) {
                    std::string query = query_module->query;
					cout <<"query " << query_module->query << endl;
                    //配置文件格式为UTF8
                    _NormalizeStmts(query_module->stmts,_query_stmts[query]);
                }
            }
      }
      mods = mods->modules;
  } 	
}


int main(int argc, char **argv) {
    YaccDriver driver;
	map<string,StmtsNormalized> _query_stmts;

    bool rc = driver.Parse(argv[1]);
    Modules *mods = driver.root;
	WalkModule(mods, _query_stmts);
    
    cout <<" parse rc=" << rc << endl;
    
    return 0;
}


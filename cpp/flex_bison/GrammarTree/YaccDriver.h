/*
 * 驱动YACC系统生成语法树。
 */
#ifndef __YaccDriver_H__
#define __YaccDriver_H__
 
#include <string>
#include <map>

#include "Node.h"
#include "YaccParser.h"
#include "DriverBase.h"

// Tell Flex the lexer's prototype ...
# define YY_DECL \
    BA::YaccParser::symbol_type yylex (BA::YaccDriver& driver)
// ... and declare it for the parser's sake.
YY_DECL;

namespace BA {

class YaccDriver
    : public DriverBase
{
public:
    YaccDriver ();
    virtual ~YaccDriver ();

    int ScanBegin (void);

    void ScanEnd (void);

    //解析文件f
    bool Parse (const std::string& f);

    // Error handling.
    void Error (const BA::location& l, const std::string& m);
    void Error (const std::string& m);

    /*反转链表*/
    BA::Modules* ReverseModuleList(BA::Modules* head)
    {
        BA::Modules* new_head = NULL;
        while (NULL != head) {
            BA::Modules* next = head->modules;
            head->modules = new_head;
            new_head = head;
            head = next;
        }
        return new_head;
    }

    BA::Stmts* ReverseStmtsList(BA::Stmts* head)
    {
        BA::Stmts* new_head = NULL;
        while (NULL != head) {
            BA::Stmts* next = head->stmts;
            head->stmts = new_head;
            new_head = head;
            head = next;
        }
        return new_head;
    }

public:
    /*语法树的根节点*/
    Modules* root;

    // The name of the file being parsed.
    // Used later to pass the file name to the location tracker.
    std::string file;
    BA::location loc;

private:
    void _InitFields(void);

    bool _LoadConf(const string& conf_file);

private:
    bool _trace_scanning;
    // Whether parser traces should be generated.
    bool _trace_parsing;
};

} /*namespace BA*/

#endif /*!__YaccDriver_H__*/

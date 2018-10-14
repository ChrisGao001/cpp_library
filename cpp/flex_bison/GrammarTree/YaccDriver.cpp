#include "YaccDriver.h"
#include "YaccParser.h"

#include <iostream>
using std::cout;
using std::endl;

extern int yylex_destroy  (void);

namespace BA {

YaccDriver::YaccDriver ()
    : _trace_scanning (false),
      _trace_parsing (false)
{
    root = NULL;
}

YaccDriver::~YaccDriver ()
{
    ReleaseNode();
    root = NULL;
}

bool YaccDriver::Parse (const std::string &f)
{
    if (root)
    {
        cout << "根节点未释放，文件未解析";
        return false;
    }

    if (f.empty())
    {
        cout << "未找到文件";
        return false;
    }

    file = f;
    if (0 > ScanBegin())
    {
        return false;
    }

    BA::YaccParser parser (*this);
    parser.set_debug_level (_trace_parsing);
    int res = parser.parse ();
    ScanEnd ();

    if (res)
    {
        yylex_destroy();
        ReleaseNode();
        return false;
    }

    return true;
}

void YaccDriver::Error (const BA::location& l, const std::string& m)
{
    cout << file << ":" << l << ": " << m << std::endl;
}

void YaccDriver::Error (const std::string& m)
{
    cout << m << std::endl;
}



} /*namespace BA*/


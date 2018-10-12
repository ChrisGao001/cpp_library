
%{ /* -*- C++ -*- flex version 2.5.35*/
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <algorithm>
#include <ctime>

#include "YaccDriver.h"
#include "YaccParser.h"
#include "Node.h"

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1

%}

%option noyywrap nounput batch debug noinput yylineno
%option outfile="lex.yy.cc"


space           [ \t\f]
newline         [\n\r]
non_newline     [^\n\r]

comment         ("#"{non_newline}*)

whitespace      ({space}+|{comment})

digit           [0-9]
ident_start     [A-Za-z\200-\377_]
ident_cont      [A-Za-z\200-\377_0-9\$]

identifier      {ident_start}{ident_cont}*

integer         {digit}+
decimal         (({digit}*\.{digit}+)|({digit}+\.{digit}*))
decimalfail     {digit}+\.\.
real            ({integer}|{decimal})[Ee][-+]?{digit}+
realfail1       ({integer}|{decimal})[Ee]
realfail2       ({integer}|{decimal})[Ee][-+]

self            [;,\<\>\=\{\}]

str             L?\"(\\.|[^\\"])*\"

other           .

%{
    // Code run each time a pattern is matched.
    # define YY_USER_ACTION  driver.loc.columns (yyleng);
%}

/*
 *
 *
 * begin difinition
 *
 */

%%

%{
    // Code run each time yylex is called.
    //driver.loc.step ();
%}


{whitespace}    {
                /* ignore */
                driver.loc.step ();
                }

{newline}       {
                    driver.loc.lines (yyleng);
                }

{identifier}    {
                    string str(yytext);
                    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

                    if("do" == str) {
                        return BA::YaccParser::make_DO(driver.loc);
                    } else if("when" == str) {
                        return BA::YaccParser::make_WHEN(driver.loc);
                    } else if("and" == str) {
                        return BA::YaccParser::make_AND(driver.loc);
                    } else if("limit" == str) {
                        return BA::YaccParser::make_LIMIT(driver.loc);
                    } else if ("mtest" == str) {
                        return BA::YaccParser::make_MTEST(driver.loc);
                    } else if("query" == str) {
                        return BA::YaccParser::make_QUERY(driver.loc);
                    } else if("hc_cid3" == str) {
                        return BA::YaccParser::make_HC_CID(driver.loc);
                    } else if("all" == str) {
                        return BA::YaccParser::make_ALL(driver.loc);
                    } else if ("position" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_POSITION,driver.loc);
                    } else if ("expire_date" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_EXPIRE_DATE,driver.loc);
                    } else if ("wareid" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_WAREID,driver.loc);
                    } else if ("warepid" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_WAREPID,driver.loc);
                    } else if ("brand_id" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_BRAND_ID,driver.loc);
                    } else if ("catid" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_CID3,driver.loc);
                    } else if ("cid2" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_CID2,driver.loc);
                    } else if ("cid1" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_CID1,driver.loc);
                    } else if ("shop_id" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_SHOP_ID,driver.loc);
                    } else if ("productext" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_PRODUCTEXT,driver.loc);
                    } else if ("xredisprice" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_XREDISPRICE,driver.loc);
                    } else if ("channel" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_CHANNEL,driver.loc);
                    } else if ("flags" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_FLAGS,driver.loc);
                    } else if ("rank_flags" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_RANK_FLAGS,driver.loc);
                    } else if ("good" == str) {
                        return BA::YaccParser::make_KEYWORD(BA::KW_GOOD,driver.loc);
                    } else {
                        driver.Error(driver.loc,"keyword<" + str + "> unknown");
                        return BA::YaccParser::make_KEYWORD(BA::KW_NONE,driver.loc);
                    }
                }

{integer}       {
                    errno = 0;
                    int64_t val = strtoll (yytext, NULL, 10);
                    if ((ERANGE == errno && (val == LLONG_MAX || val == LLONG_MIN))
                        || (errno != 0 && val == 0))
                    {
                        string str(yytext);
                        driver.Error(driver.loc,"interger:" + str + " out of range");
                        return BA::YaccParser::make_TOC_UNKNOWN(driver.loc);
                    }
                    else
                    {
                        return BA::YaccParser::make_INTEGER(val, driver.loc);
                    }
                }

{decimal}       {
                double val = atof(yytext);
                return BA::YaccParser::make_DOUBLE(val, driver.loc);
                }

{self}          {
                    char c = yytext[0];
                    switch (c)
                    {
                    case '(':
                        return BA::YaccParser::make_LPAREN(driver.loc);
                    case ')':
                        return BA::YaccParser::make_RPAREN(driver.loc);
                    case '{':
                        return BA::YaccParser::make_LBRACE(driver.loc);
                    case '}':
                        return BA::YaccParser::make_RBRACE(driver.loc);
                    case '=':
                        return BA::YaccParser::make_ASSIGN(driver.loc);
                    case '<':
                        return BA::YaccParser::make_LT_OP(driver.loc);
                    case '>':
                        return BA::YaccParser::make_GT_OP(driver.loc);
                    case ';':
                        return BA::YaccParser::make_SEMICOLON(driver.loc);
                    case ',':
                        return BA::YaccParser::make_COMMA(driver.loc);
                    default:
                        break;
                    }
                }

{str}           {
                    string str(yytext);

                    if (str.size() < 2) {
                        driver.Error(driver.loc,"string size wrong");
                    } else {
                        str = str.substr(1,str.size() - 2);
                    }

                    tm tm_t;
                    memset(&tm_t,0,sizeof(tm_t));

                    int ret = sscanf(str.c_str(), "%04d-%02d-%02d %02d:%02d:%02d",
                                &tm_t.tm_year,
                                &tm_t.tm_mon,
                                &tm_t.tm_mday,
                                &tm_t.tm_hour,
                                &tm_t.tm_min,
                                &tm_t.tm_sec);

                    if (6 != ret) {
                        return BA::YaccParser::make_STRING(str,driver.loc);
                    } else {
                        /*匹配到日期，对日期特殊处理*/
                        tm_t.tm_year -= 1900;
                        tm_t.tm_mon -= 1;

                        return BA::YaccParser::make_INTEGER((int64_t)mktime(&tm_t),driver.loc);
                    }
                }

"+="            {
                    return BA::YaccParser::make_ADD_ASSIGN(driver.loc);
                }

"-="            {
                    return BA::YaccParser::make_SUB_ASSIGN(driver.loc);
                }

"*="            {
                    return BA::YaccParser::make_MUL_ASSIGN(driver.loc);
                }

"<="            {
                    return BA::YaccParser::make_LE_OP(driver.loc);
                }

">="            {
                    return BA::YaccParser::make_GE_OP(driver.loc);
                }

"=="            {
                    return BA::YaccParser::make_EQ_OP(driver.loc);
                }

"!="            {
                    return BA::YaccParser::make_NE_OP(driver.loc);
                }

{other}         {
                    return BA::YaccParser::make_TOC_UNKNOWN(driver.loc);
                }


<<EOF>>         return BA::YaccParser::make_END(driver.loc);

%%

namespace BA {

int YaccDriver::ScanBegin (void)
{
    yy_flex_debug = _trace_scanning;

    if (!(yyin = fopen (file.c_str (), "r")))
    {
        Error ("cannot open " + file + ": " + strerror(errno));
        return -1;
    }

    return 0;
}

void YaccDriver::ScanEnd (void)
{
    if (yyin) fclose (yyin);
}

} /*namespace BA*/

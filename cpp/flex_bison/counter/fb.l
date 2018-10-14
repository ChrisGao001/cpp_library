%{
#include <stdio.h>
int num_char = 0;
int num_word = 0;
int num_line = 0;
%}

%%
[a-zA-Z]+ { num_char += yyleng; num_word+=1;}
\n { num_char += 1; num_line += 1;}
. {num_char += 1;}
%%

int main(int argc, char **argv) {
    yylex();
    printf("num_char=%d,num_word=%d,num_line=%d\n", num_char, num_word, num_line);
    return 0;
}

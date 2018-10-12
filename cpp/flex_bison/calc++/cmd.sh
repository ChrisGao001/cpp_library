set -x
flex calc++-scanner.ll
bison -vd calc++-parser.yy
#g++ -o calc calc++.cc calc++-driver.cc *.cc  lex.yy.c -I./

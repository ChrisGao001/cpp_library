all : BusynessAdjust run
BusynessAdjust : main.cpp Node.cpp YaccDriver.cpp  YaccParser.cpp
	flex ba.ll
	pkg/bison/bin/bison -vd ba.yy
	g++ -o BusynessAdjust $^ lex.yy.cc  -I./
.Phony clean:
	rm -f BusynessAdjust

run: BusynessAdjust
	./BusynessAdjust ./adjust.txt

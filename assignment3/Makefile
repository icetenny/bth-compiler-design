compiler: lex.yy.c parser.tab.o main.cc
		g++ -g -w -ocompiler parser.tab.o lex.yy.c main.cc -std=c++14
parser.tab.o: parser.tab.cc
		g++ -g -w -c parser.tab.cc -std=c++14
parser.tab.cc: parser.yy
		bison parser.yy
lex.yy.c: lexer_assignment1.flex parser.tab.cc
		flex lexer_assignment1.flex
tree: 
		 dot -Tpdf tree.dot -o tree.pdf
st: 
		 dot -Tpdf st.dot -o st.pdf
ir: 
		 dot -Tpdf ir_tree.dot -o ir_tree.pdf
clean:
		rm -f parser.tab.* lex.yy.c* compiler stack.hh position.hh location.hh tree.dot tree.pdf interpreter
		rm -R compiler.dSYM
interpreter: interpreter.cc
	g++ -std=c++14 -g -w interpreter.cc -o interpreter

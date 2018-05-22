CC:=/usr/bin/gcc

while:	lexer.l
	flex lexer.l
	${CC} -o $@ lex.yy.c -lfl

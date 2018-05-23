SRCS := parser.tab.c lex.yy.c ast.c pretty.c env.c interp.c main.c
OBJS := $(patsubst %.c,%.o,$(SRCS))

all:	pp while

parser.tab.c parser.tab.h:	parser.y
	bison --defines parser.y

lex.yy.c:	lexer.x parser.tab.h
	flex lexer.x

depend:	.depend

.depend:	$(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM -I. $^ > ./.depend;

include .depend

pp:	parser.tab.o lex.yy.o ast.o pretty.o pp.o
	$(CC) $(CFLAGS) -o $@ $^ -lfl -std=gnu99

while:	parser.tab.o lex.yy.o ast.o pretty.o env.o interp.o main.o
	$(CC) $(CFLAGS) -o $@ $^ -lfl -std=gnu99

clean:
	rm -f *.o parser.tab.* lex.yy.* while .depend

CC  = gcc 
LEX = flex
YACC = bison -d 
HDRS = basic.tab.h 
LDFLAGS = -lfl -ly 
LIBS = 
OBJS = basic.tab.o lex.yy.o ast.o 
PROGRAM = basic.out
all: $(PROGRAM) 
$(PROGRAM):	$(OBJS) $(HDRS) 
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(PROGRAM) 
lex.yy.c:  basic.l 
	$(LEX) basic.l 
lex.yy.o: lex.yy.c
	$(CC) lex.yy.c -c
basic.tab.c: basic.y 
	$(YACC) basic.y
basic.tab.o:
	$(CC) basic.tab.c -c 
ast.o: ast.c ast.h
	$(CC) ast.c -c
clean:
	rm -f *.o *~ 

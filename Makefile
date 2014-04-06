LEX=flex
YACC=bison
CC=gcc
OBJECT=expr_parser

$(OBJECT): expr_parser.c parser.c parser.h lexer.c lexer.h expression.c expression.h
	$(CC) expr_parser.c parser.c lexer.c expression.c -o $(OBJECT)

parser.c parser.h: parser.y
	$(YACC) -d -o parser.c parser.y

lexer.c lexer.h: lexer.l
	$(LEX) -o lexer.c --header-file="lexer.h" lexer.l

clean:
	@rm -f $(OBJECT) parser.c parser.h lexer.c lexer.h *.gch


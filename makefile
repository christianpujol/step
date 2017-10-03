CC=gcc
CFLAGS=-Wall -Wno-unused-function

step: step.c papercomputer.c lex.yy.c
	$(CC) $(CFLAGS) $^  -lfl -o $@

lex.yy.c: step.lex
	flex $^

clean:
	-rm lex.yy.c step *~

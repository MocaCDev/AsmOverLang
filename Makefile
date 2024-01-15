FILES=main.c backend/token.c backend/lexer.c backend/asm_code.c backend/parser.c
CC=gcc -fsanitize=leak
O=-o main.o

.PHONY: main.o
.PHONY: run
.PHONY: clean

run: main.o
	./main.o

main.o: clean
	$(CC) $(FILES) $(O)
	
clean:
	rm -rf *.o

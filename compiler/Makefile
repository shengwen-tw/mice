ELF=mice_cc

CFLAGS+=-I./

SRC=main.c \
	lexer.c \
	syntax_parser.c

all: $(SRC)
	gcc -o $(ELF) $^

clean:
	rm -rf $(ELF)

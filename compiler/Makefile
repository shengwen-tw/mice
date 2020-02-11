ELF=mice_cc

CFLAGS+=-I./

SRC=main.c \
	lex_scanner.c

all: $(SRC)
	gcc -o $(ELF) $^

clean:
	rm -rf $(ELF)

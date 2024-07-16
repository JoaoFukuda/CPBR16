all: desafio

desafio: desafio.c
	gcc -z execstack -fno-stack-protector -o $@ $<

clean:
	@rm -f desafio

.PHONY: all clean

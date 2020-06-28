all: Parser Scanner YourCode 
	gcc BabyC.tab.o lex.yy.o driver.o your_code.o symbol_table.o code_gen.o -o bcc

YourCode: your_code.o driver.o symbol_table.o code_gen.o

Scanner: BabyC.lex 
	flex BabyC.lex
	gcc -c lex.yy.c

Parser: BabyC.y  
	bison -d BabyC.y
	gcc -c BabyC.tab.c

%.o: %.c 
	gcc -c $<


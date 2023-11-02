CC      	:= /usr/bin/gcc
CFLAGS  	:= -Wall -pedantic -Wextra -std=c99 -O0 -g3 -fsanitize=undefined,address
LDFLAGS		:=

log_with_macro: log_with_macro.o
	$(CC) $(CFLAGS) $< -o $@

log_with_macro.o: log_with_macro.c
	$(CC) $(CFLAGS) -Wno-unused-parameter -c $< -o $@

clean:
	$(RM) log_with_macro.o
	$(RM) log_with_macro
	$(RM) example.log


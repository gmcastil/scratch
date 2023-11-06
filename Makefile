CC      	= /usr/bin/gcc
CFLAGS  	= -Wall -pedantic -Wextra -std=c99 -O0 -g3 -fsanitize=undefined,address
TARGETS		= log_with_macro trim_with_isspace

vpath %.c src
vpath %.h src

all: log_with_macro trim_with_isspace

%: %.c
	$(CC) $(CFLAGS) -Wno-unused-parameter $< -o $@

clean:
	$(RM) log_with_macro
	$(RM) example.log
	$(RM) trim_with_isspace


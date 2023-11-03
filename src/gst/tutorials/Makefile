CC		:= /usr/bin/gcc
CFLAGS		:= -Wall -Wextra -g

GST_CFLAGS	:= $(shell pkg-config --cflags gstreamer-1.0)
GST_LDFLAGS	:= $(shell pkg-config --libs gstreamer-1.0)

CFLAGS		+= $(GST_CFLAGS)

basic-tutorial-1: basic-tutorial-1.o
	$(CC) $< $(GST_LDFLAGS) -o $@ 

basic-tutorial-1.o: basic-tutorial-1.c
	$(CC) $(CFLAGS) -c $< -o $@

basic-tutorial-2: basic-tutorial-2.o
	$(CC) $< $(GST_LDFLAGS) -o $@ 

basic-tutorial-2.o: basic-tutorial-2.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) basic-tutorial-1.o
	$(RM) basic-tutorial-1
	$(RM) basic-tutorial-2.o
	$(RM) basic-tutorial-2


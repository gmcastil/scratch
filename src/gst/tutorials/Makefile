CC		:= /usr/bin/gcc
CFLAGS		:= -Wall -Wextra -g

GST_CFLAGS	:= $(shell pkg-config --cflags gstreamer-1.0)
GST_LDFLAGS	:= $(shell pkg-config --libs gstreamer-1.0)

CFLAGS		+= $(GST_CFLAGS)

GST_TUTORIALS	:= \
			basic-tutorial-1 \
			basic-tutorial-2 \
			basic-tutorial-3

all: $(GST_TUTORIALS)

basic-tutorial-3: basic-tutorial-3.o
	$(CC) $< $(GST_LDFLAGS) -o $@ 

basic-tutorial-2: basic-tutorial-2.o
	$(CC) $< $(GST_LDFLAGS) -o $@ 

basic-tutorial-1: basic-tutorial-1.o
	$(CC) $< $(GST_LDFLAGS) -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) basic-tutorial-1.o
	$(RM) basic-tutorial-1
	$(RM) basic-tutorial-2.o
	$(RM) basic-tutorial-2
	$(RM) basic-tutorial-3.o
	$(RM) basic-tutorial-3


TARGET=pipe2
CSRC=$(TARGET).c
CSRC+=

CC=gcc
DEBUG=gdb3
OPT=3

CDEFS=

CFLAGS=-g$(DEBUG) -O$(OPT) $(CDEFS) -m32
LDFLAGS=-lm -m32

COBJ=$(CSRC:.c=.o)

$(TARGET): $(COBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
		
$(COBJ:%.o): %.c
	$(CC) $(CFLAGS) $(CDEFS) -c $<

clean:
	rm -f $(TARGET) $(COBJ)

.PHONY: clean

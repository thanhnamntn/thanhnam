.PHONY: all, clean 
TARGET = run 
CSRCS = $(wildcard *.c)
#OBJS = $(patsubst %.c, %.o, $(CSRCS))
LDFLAGS += -L./lib -serial
CC = gcc
#HDRS = serial.h

all: $(TARGET) 
$(TARGET): $(CSRCS)
		$(CC) -o $(TARGET) $(LDFLAGS)
#%.o: %.c $(HDRS) 
#	$(CC) -c $< -o $@ 
clean:
	rm -rf $(TARGET) 
#	rm -rf $(OBJS)


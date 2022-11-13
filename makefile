CC := gcc
CFLAGS := -Wall -pedantic -std=c17
OBJS := src/main.o \
src/env/envhelper.o

all: build

build: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

$(OBJS): clean
$(OBJS): %.o : %.c

clean:
	rm -f $(OBJS)
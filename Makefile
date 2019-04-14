OBJS = smash.o commands.o history.o
RULES = rules.d
EXE = smash
CFLAGS = -Wall -std=c99 -D _BSD_SOURCE
RFLAGS = -MM
CC = gcc -g

all: $(RULES) $(EXE)

$(RULES): $(wildcard *.c) $(wildcard *.h)
	$(CC) $(RFLAGS) $(wildcard *.c) > rules.d

-include rules.d

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) $(EXE) $(RULES)

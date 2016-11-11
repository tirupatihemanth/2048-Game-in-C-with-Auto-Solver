#Makefile
#

CFLAGS = -c
LDFLAGS = `pkg-config --cflags --libs gtk+-2.0` -lm

all: backend.o frontend.o ai.o
	gcc  $^ -o 2048_game $(LDFLAGS)
backend.o: backend.c backend.h
	gcc $(CFLAGS) $< -o $@ $(LDFLAGS)

frontend.o: frontend_2048.c
	gcc $(CFLAGS) $< -o $@ $(LDFLAGS)

ai.o: 2048_AI.c 2048_AI.h
	gcc $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f *.o
	rm -f 2048_game

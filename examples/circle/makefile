CC = gcc -O3 -Wall
TAIL = -lm

all: Aarea1 Aarea2 Aarea3 Aarea4 Amixedmode

Aarea1: area1.c
	scc area1.c
	$(CC) -o Aarea1 area1.c $(TAIL)

Aarea2: area2.c
	scc area2.c
	$(CC) -o Aarea2 area2.c $(TAIL)

Aarea3: area3.c
	scc area3.c
	$(CC) -o Aarea3 area3.c $(TAIL)

Aarea4: area4.c
	scc area4.c
	$(CC) -o Aarea4 area4.c $(TAIL)

Amixedmode: mixedmode.c
	scc mixedmode.c
	$(CC) -o Amixedmode mixedmode.c $(TAIL)

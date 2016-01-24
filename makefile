flags=-O2 -Wall -Wextra -pedantic -Wstrict-overflow -fno-strict-aliasing

all:
	gcc -c ${flags} wisdoms.c
	gcc ${flags} sophos.c -o sophos

clean:
	rm sophos *.o

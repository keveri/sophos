flags=-std=c11 -O2 -Wall -Wextra -pedantic -Wstrict-overflow -fno-strict-aliasing

all:
	gcc ${flags} -c src/wisdoms.c -o /dev/null
	gcc ${flags} src/sophos.c -o bin/sophos

clean:
	rm bin/sophos

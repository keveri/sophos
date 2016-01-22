executable=sophos

all:
	gcc -O2 -Wall -Wextra -pedantic -Wstrict-overflow -fno-strict-aliasing \
	    ${executable}.c -o ${executable}

clean:
	rm ${executable}

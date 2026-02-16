clean: test.exe BigInteger.o
	rm -f *.o

test.exe: tests.c BigInteger.o
	gcc -std=c99 -o test tests.c BigInteger.o

BigInteger.o: BigInteger.c
	gcc -std=c99 -c BigInteger.c

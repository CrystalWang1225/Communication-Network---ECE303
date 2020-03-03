scanner.exe: main.o
	gcc -o scanner.exe main.o
main.o: main.c
	gcc -c main.c -I
clean:
	rm -f .*exe *.o *.stackdump


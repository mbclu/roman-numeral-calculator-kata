all: rnc.exe

rnc.exe: main.o
	gcc -o rnc.exe main.o

main.o: main.c
	gcc -c main.c

clean:
	rm main.o rnc.exe


output: main.o MyLib.o
	gcc main.o MyLib.o -o main.exe

main.o: main.c
	gcc -c main.c

MyLib.o: MyLib.c MyLib.h
	gcc -c MyLib.c

static: 
	gcc -c MyLib.c
	ar rcs MyLib.a MyLib.o
	gcc -c main.c
	gcc main.o MyLib.a -o main.exe

shared: 
	gcc -fPIC -c MyLib.c -o MyLib.o
	gcc -fPIC -shared -o libMyLib.so MyLib.o
	gcc -Wl,-rpath=. -L. -o main.exe main.c -lMyLib

clean: 
	rm *.o
	rm main.exe
	truncate -s 0 raport2a.txt
clean_static:
	rm *.a
	rm *.o
	rm main.exe
	truncate -s 0 raport2a.txt
clean_shared:
	rm *.so
	rm *.o
	rm main.exe
	truncate -s 0 raport2a.txt

run:
	./main.exe 30000 300 d d20000 D20000
	./main.exe 3000 3000 d s200 
	./main.exe 30000 300 s d20000
	./main.exe 3000 3000 s D2000
	./main.exe 3000 3000 s s200
	./main.exe 300 30000 d s200
	./main.exe 300 30000 s s200

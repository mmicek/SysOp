
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
	gcc main.o MyLib.a -o main_static.exe

shared: 
	gcc -fPIC -c MyLib.c -o MyLib.o
	gcc -fPIC -shared -o libMyLib.so MyLib.o
	gcc -Wl,-rpath=. -L. -o main_shared.exe main.c -lMyLib

dynamic:
	gcc -fPIC -c MyLib.c -o MyLib.o 
	gcc -Wl,-rpath=. -fPIC -shared -o libMyLib.so MyLib.o 
	gcc -fPIC -L. -o main_dynamic.exe main_d.c -ldl -D DYNAMIC 

compile:
	static

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
clean_dynamic:
	rm *.so
	rm *.o
	rm main.exe
	truncate -s 0 raport2a.txt
clean_all:
	

run:
	echo "###########STATIC: \n\n" >> raport2a.txt
	./main_static.exe 30000 300 d d20000 D20000
	./main_static.exe 3000 3000 d s200 
	./main_static.exe 30000 300 s d20000
	./main_static.exe 3000 3000 s D2000
	./main_static.exe 3000 3000 s s200
	./main_static.exe 300 30000 d s200
	./main_static.exe 300 30000 s s200
	echo "############SHARED: \n\n" >> raport2a.txt
	./main_shared.exe 30000 300 d d20000 D20000
	./main_shared.exe 3000 3000 d s200 
	./main_shared.exe 30000 300 s d20000
	./main_shared.exe 3000 3000 s D2000
	./main_shared.exe 3000 3000 s s200
	./main_shared.exe 300 30000 d s200
	./main_shared.exe 300 30000 s s200
	echo "#############DYNAMIC: \n\n" >> raport2a.txt
	./main_dynamic.exe 30000 300 d d20000 D20000
	./main_dynamic.exe 3000 3000 d s200 
	./main_dynamic.exe 30000 300 s d20000
	./main_dynamic.exe 3000 3000 s D2000
	./main_dynamic.exe 3000 3000 s s200
	./main_dynamic.exe 300 30000 d s200
	./main_dynamic.exe 300 30000 s s200

all:main

main: main.o fecha.o cadena.o
	g++  main.o fecha.o cadena.o -o main
	./main
	

main.o: main.cpp fecha.hpp cadena.hpp
	g++ -c main.cpp  

fecha.o: fecha.cpp fecha.hpp
	g++ -c fecha.cpp

cadena.o: cadena.cpp cadena.hpp
	g++ -c cadena.cpp

clean: 
	rm main.o fecha.o cadena.o main
	clear

clean_win:
	del main.o fecha.o cadena.o main.exe
	cls
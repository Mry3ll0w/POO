all:main

main: main.o articulo.o usuario.o tarjeta.o fecha.o cadena.o
	g++  main.o articulo.o usuario.o tarjeta.o fecha.o cadena.o -o main -lcrypt -fPIE
	./main

debug:
	g++ -g main.cpp 	

main.o: main.cpp articulo.hpp usuario.hpp
	g++ -c main.cpp  

articulo.o: articulo.cpp articulo.hpp
	g++ -c articulo.cpp

usuario.o: usuario.cpp usuario.hpp
	g++ -c usuario.cpp

tarjeta.o: tarjeta.cpp tarjeta.hpp
	g++ -c tarjeta.cpp

fecha.o: ../P1/fecha.cpp ../P1/fecha.hpp
	g++ -c ../P1/fecha.cpp
cadena.o: ../P1/cadena.cpp ../P1/cadena.hpp
	g++ -c ../P1/cadena.cpp	 
clean: 
	rm usuario.o cadena.o fecha.o main.o tarjeta.o articulo.o 
	clear

clean_win:
	del main.o fecha.o cadena.o main.exe
	cls
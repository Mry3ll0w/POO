all:main

main: main.o articulo.o usuario.o tarjeta.o
	g++  main.o articulo.o usuario.o tarjeta.o -o main -lcrypt
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

clean: 
	rm usuario.o cadena.o fecha.o main.o tarjeta.o articulo.o
	clear

clean_win:
	del main.o fecha.o cadena.o main.exe
	cls


VPATH = ../Tests-auto:.


CXX = g++								  

CPPFLAGS = -I../Tests-auto -I. -DP1      
CXXFLAGS = -g -Wall -pedantic -std=c++11 -fpermissive  
LDFFLAGS = 								

all: test-P0-auto test-fechacadena-consola

test-P0-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o \
			  test-auto.o cadena.o fecha.o #el \ sirve para que siga leyendo abajo
	$(CXX) -o $@ $(LDFLAGS) $^

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $^
	
test-fechacadena-consola: test-fechacadena-consola.o fecha.o cadena.o
	$(CXX) -o $@ $(LDFLAGS) $^

clean: 
	$(RM) *.o test-P0-auto test-P0-consola





#include <iostream>
#include "fecha.hpp"
#include "cadena.hpp"
#include <ctime>


int main(){
     Fecha a(3,6,2001),b;
     Cadena cad;
     cad = a;
     cad.show();
     return 0;
}
#include <iostream>
#include "fecha.hpp"
#include "cadena.hpp"
#include <ctime>


int main(){
     Cadena a("el"),b(" pepe");
     a=a+b;
     cout<<a<<endl;
     return 0;
}
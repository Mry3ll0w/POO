#include <iostream>
#include "fecha.hpp"
#include "cadena.hpp"
#include <ctime>


int main(){
     int n=1;
     Fecha a("12/1/2000"),b;
     a=a+12;
     cout<<a<<endl;
     return 0;
}
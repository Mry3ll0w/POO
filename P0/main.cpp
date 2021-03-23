#include <iostream>
#include "fecha.hpp"
#include "cadena.hpp"
#include <ctime>


int main(){
     Cadena a("pep"),b("illo");
     a=b+b;
     cout<<a<<endl;
     return 0;
}
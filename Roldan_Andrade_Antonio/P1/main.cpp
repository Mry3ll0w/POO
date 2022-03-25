#include <iostream>
#include "fecha.hpp"
#include "cadena.hpp"
#include <ctime>
int main(){
     Fecha f(1, 1, 2010);
      const Fecha g(----f);

    std::cout<<"f:"<<  f <<std::endl;
    std::cout<<"g:"<< g <<std::endl;
}
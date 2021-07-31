#include <iostream>
#include "m_dispersa.hpp"

bool cosita(size_t a , size_t b){
    return a<b;
}
int main(){ 
    
    /* Ejercicio 5 */
    MatrizDispersa a(5,4);
    /* {{},{},{},{},{4,2,61.5}}; */
    a.asignar(0,1,7.5);
    a.asignar(2,0,18.2);
    a.asignar(2,2,86.37);
    a.asignar(3,3,10.25);
    a.asignar(4,2,61.5);
    a.print_matrix();
    std::cout<< cosita(2,2)<<std::endl;
    return 0;
}
#include <iostream>
#include "Binario.hpp"


int main(){
     binario a;
     binario b(4);
     a.show_bits();
     b.show_bits();
     //b = ~a(); PREGUNTAR DANI
     b = std::move(a);
     b.show_bits();
     return 0;
}

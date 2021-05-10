#include "pedido-articulo.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& salida, const LineaPedido& l) {
    salida << std::setprecision(2);
    salida << l.precio_venta()<<" "<<"€"<<"\t"<<l.cantidad()<<std::endl;
}

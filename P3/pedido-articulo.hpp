#ifndef PEDIDO-ARTICULO_HPP
#define PEDIDO-ARTICULO_HPP
#include<iostream> 
#include <iomanip> 
#include "../P2/articulo.hpp" 
#include "pedido.hpp" 

class LineaPedido{ 
 private: 
    double precio_de_venta; 
    unsigned cantidad_;

 public: 

    explicit LineaPedido(double p_venta, unsigned cantidad__=1):cantidad_(cantidad__){
        precio_de_venta=p_venta;
    } 

    const double precio_venta() const noexcept {
        return precio_de_venta;
    }

    const unsigned cantidad() const noexcept {
        return cantidad_;
    } 
  
};
std::ostream& operator<<(std::ostream&, const LineaPedido&);


class Pedido; 
class Articulo;




#endif
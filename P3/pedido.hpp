#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include "../P2/usuario.hpp" 
#include "../P2/tarjeta.hpp" 
#include "../P1/fecha.hpp" 
#include "../P1/cadena.hpp"
#include "../P2/articulo.hpp" 
//#include "pedido-articulo.hpp" 
//#include "usuario-pedido.hpp" 
#include<iomanip> 
#include<iostream> 
class Pedido
{
private:
    int numero_pedido;
    const Tarjeta* tarjeta_;
    Fecha fecha_pedido;
    static unsigned pedidos_realizados; 
public:
    Pedido();//Falta la clase  Usuario Pedido y la clase pedido_articulo
    ~Pedido();
};




#endif
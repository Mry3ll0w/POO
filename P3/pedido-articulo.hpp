#ifndef PEDIDO-ARTICULO_HPP
#define PEDIDO-ARTICULO_HPP
#include<iostream> 
#include <map>
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
class OrdenaPedidos: public std::binary_function<Pedido*,Pedido*,bool>{ 
public: 
    bool operator()( Pedido* p1, Pedido* p2) const{
        return (p1->numero() < p2->numero());
    } 
};
class OrdenaArticulos: public std::binary_function<Articulo*,Articulo*,bool>{ 
 public: 
    bool operator()(Articulo* a1, Articulo* a2) const {
        return (a1->referencia() < a2->referencia());
    } 
};

class Pedido_Articulo{       
    public:

/* ---------------------------------- TIPOS --------------------------------- */

        typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido; 
        typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos; 
        typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> Pedidos_Articulos; 
        typedef std::map<Articulo*, Pedidos, OrdenaArticulos> Articulos_Pedidos;

/* --------------------------------- METODOS -------------------------------- */
        void pedir(Pedido& , Articulo& , double , unsigned c=1);
        void pedir(Articulo& , Pedido& , double , unsigned c=1);
        
        const ItemsPedido& detalle(Pedido& p){
            return pedidos_articulos_.find(&p)->second;//busca el pedido introducido y devuelve la referencia
        }
        
        Pedidos ventas(Articulo& a){
            if(articulos_pedidos_.find(&a)!=articulos_pedidos_.end())
                return articulos_pedidos_.find(&a)->second; 
            else
                Pedido_Articulo::Pedidos vacio; 
                return vacio;  
        } 
        std::ostream& mostrarDetallePedidos(std::ostream&) const;  
        std::ostream& mostrarVentasArticulos(std::ostream&) const; 
 
 private:  
    Pedidos_Articulos pedidos_articulos_; 
    Articulos_Pedidos articulos_pedidos_; 
};
std::ostream& operator<<(std::ostream& salida, Pedido_Articulo::ItemsPedido itemspedido)noexcept;
ostream& operator <<(ostream& salida,const Pedido_Articulo::Pedidos& p) noexcept;

#endif
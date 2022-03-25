#include "pedido-articulo.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& salida, const LineaPedido& l) {
    salida<<std::fixed;
    salida << std::setprecision(2);
    salida << l.precio_venta()<<" €"<<"\t"<<l.cantidad()<<std::endl;
    return salida;
}

void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double pr, unsigned c) {
    pedidos_articulos_[&p].insert(make_pair(&a,LineaPedido(pr,c))); 
    articulos_pedidos_[&a].insert(make_pair(&p,LineaPedido(pr,c)));
}

void Pedido_Articulo::pedir(Articulo& a , Pedido& p, double pr , unsigned c){
    pedir(p, a, pr,c);//Llama al superior con el orden cambiado
}

/* ------------------- sobrecargas a los flujos de salida ------------------- */

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream&salida) const {
    double pr=0; 
    for(auto i : pedidos_articulos_){ 
        salida << "Pedido núm. " << i.first->numero(); 
        salida << "\tCliente: " << i.first->tarjeta()->titular()->nombre() << " \n"; 
        salida << "Fecha: " << i.first->fecha() << i.second; 
        pr += i.first->total(); 
    } 
    salida<< fixed<< setprecision(2);
    salida << "TOTAL VENTAS: " << pr << " €" << std::endl;
    return salida; 
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& salida) const {
    for(auto i: articulos_pedidos_){ 
        salida << "Ventas de " << "[" << i.first->referencia() << "]"; 
        salida << "\"" << i.first->titulo() << "\" \n" << i.second << std::endl; 
    } 
    return salida; 
}

ostream& operator <<(ostream& salida,const Pedido_Articulo::Pedidos& p) noexcept
{ 
    double pr = 0; 
    unsigned total = 0; 
    Pedido_Articulo::Pedidos::const_iterator i; 
    salida << "====================================================\n" << std::endl; 
    salida << " PVP \t Cant. \t Fecha venta \n"; 
    salida << "====================================================\n" << std::endl; 
    for(auto j : p){ 
        salida << " " << j.second.precio_venta() << "€\t"; 
        salida << j.second.cantidad() << "\t"<< j.first->fecha() << std::endl; 
        pr += (j.second.precio_venta() * j.second.cantidad()); 
        total += j.second.cantidad(); 
    } 
    salida << "====================================================\n" << std::endl; 
    salida << fixed; 
    salida << setprecision(2) << pr << " €\t" << total <<endl ; 
    return salida; 
}

std::ostream& operator<<(std::ostream& salida, Pedido_Articulo::ItemsPedido itemspedido)noexcept{
    double pr = 0; 
    Pedido_Articulo::ItemsPedido::const_iterator i; 
    salida << std::endl << "====================================================\n" << std::endl; 
    salida << " PVP \t Cant. \t Articulo \n"; 
    salida << "====================================================\n" << std::endl; 
    for(i = itemspedido.begin(); i != itemspedido.end(); ++i){ 
        salida << " " << i->second.precio_venta() << "€\t"<< i->second.cantidad() << "\t"<< "[" << i->first->referencia() << "] "; 
        salida << "\"" << i->first->titulo() << "\" " << std::endl; 
        pr = pr + i->second.precio_venta() * i->second.cantidad(); 
    } 
    salida << "===================================================\n" << std::endl; 
    salida << fixed; 
    salida << setprecision(1) << pr << " €" << std::endl; 
    return salida;
}

bool OrdenaPedidos::operator()(Pedido* p1, Pedido* p2)const
{
    return (p1->numero() < p2->numero());
} 

bool OrdenaArticulos::operator()(Articulo* a1, Articulo* a2)const{
        return (a1->referencia() < a2->referencia());
} 

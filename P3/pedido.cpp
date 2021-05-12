#include "pedido.hpp"
Pedido::Pedido(Usuario_Pedido& u_p, Pedido_Articulo& p_a, Usuario& us, const Tarjeta& tarjeta, const Fecha& f)
    : numero_ped_(numero_ped_+1),
      tarjeta_pago_(&tarjeta),
      importe_total_(0.00),//se calcula a posteriori
      fecha_pedido_(f)
{

/* --------------------- excepciones en la construccion --------------------- */

    if (us.compra().empty()==true)
    {
      throw Pedido::Vacio(&us);
    }
    
    if (tarjeta.titular()!=&us)
    {
      throw Pedido::Impostor(&us);
    }
    
    for (auto i:us.compra())
    {
      
      if (i.first->stock()<i.second)//si la cantidad solicitada supera a las existencias
      {
        for (auto j:us.compra())
        {
          us.compra(*j.first,0);//vaciamos el carro y lanzamos sin stock
        }
        throw Pedido::SinStock(i.first);
      }
      
    }
    u_p.asocia(*this,us);//asociamos el user al pedido
    for (auto i:us.compra())
    {
      importe_total_+=i.first->precio()*i.second; //importe=precio*cantidad
      p_a.pedir(*i.first,*this,i.first->precio(),i.second);
      i.first->stock()-=i.second;//actualizamos la cantidad
    }
    n_pedidos_totales_++;//Aumentamos el numero de pedidos realizados

    

}

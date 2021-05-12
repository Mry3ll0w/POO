#include "pedido.hpp"
unsigned Pedido::n_ped_t_=0;
Pedido::Pedido(Usuario_Pedido& u_p, Pedido_Articulo& p_a, Usuario& us, const Tarjeta& tarjeta, const Fecha& f)
    : numero_ped_(numero()+1),
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
    if (tarjeta.activa()==false)
    {
      Tarjeta::Desactivada des;
      throw des;
    }
    
    for (auto i:us.compra())
    {
      
      if (i.first->stock()<i.second)//si la cantidad solicitada supera a las existencias
      {
        for (auto j:us.compra())
        {
          us.compra(*j.first,0);//vaciamos el carro y lanzamos sin stock
        }
        //throw Pedido::SinStock(i.first);
      }
      
    }
    u_p.asocia(*this,us);//asociamos el user al pedido
    for (auto i:us.compra())
    {
      p_a.pedir(*i.first,*this,i.first->precio(),i.second);
      importe_total_+=i.first->precio()*i.second; //importe=precio*cantidad
      i.first->stock()-=i.second;//actualizamos la cantidad
    }
    n_ped_t_++;//Aumentamos el numero de pedidos realizados
}
std::ostream& operator<<(std::ostream& salida, const Pedido& p){
    salida<<"Núm. pedido: "<<p.numero()<<std::endl;
    salida<<"Fecha: "<<p.fecha()<<std::endl;
    salida<<"Pagado con: "<<p.tarjeta()<<endl;
    salida<<"Importe: "<<p.total()<<std::endl;
    return salida;
}
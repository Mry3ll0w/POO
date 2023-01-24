#include "pedido.hpp"
unsigned Pedido::n_ped_t_ = 0;
Pedido::Pedido(Usuario_Pedido &u_p, Pedido_Articulo &p_a, Usuario &us, const Tarjeta &tarjeta, const Fecha &f)
    : numero_ped_(n_ped_t_ + 1),
      tarjeta_pago_(&tarjeta),
      importe_total_(0.00),
      fecha_pedido_(f)
{

  if (us.compra().empty() == true)
  {
    throw Pedido::Vacio(&us);
  }

  if (tarjeta.titular() != &us)
  {
    throw Pedido::Impostor(&us);
  }

  if (tarjeta.activa() == false)
  {
    Tarjeta::Desactivada des;
    throw des;
  }

  if (tarjeta.caducidad() < f)
  {
    throw Tarjeta::Caducada(tarjeta.caducidad());
  }

  for (auto i : us.compra())
  {

    if (i.first->stock() < i.second)
    {
      for (auto j : us.compra())
      {
        us.compra(*j.first, 0);
      }
      throw Pedido::SinStock(i.first);
    }
  }
  u_p.asocia(*this, us);
  auto temporal = us.compra();
  for (auto i : temporal)
  {

    us.compra(*i.first, 0);
    p_a.pedir(*this, *i.first, i.first->precio(), i.second);
    importe_total_ += i.first->precio() * i.second;
    i.first->stock() -= i.second;
  }
  ++n_ped_t_;
}

std::ostream &operator<<(std::ostream &salida, const Pedido &p)
{
  salida << "Núm. pedido: " << p.numero() << std::endl;
  salida << "Fecha: " << p.fecha() << std::endl;
  salida << "Pagado con: " << *p.tarjeta() << endl;
  salida << "Importe: " << p.total() << " €" << std::endl;
  return salida;
}
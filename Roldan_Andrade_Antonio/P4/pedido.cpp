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
  auto t = us.compra();
  for (Usuario::art::iterator i = t.begin(); i != t.end(); ++i)
  {

    if (ArticuloAlmacenable *art_almacenable = dynamic_cast<ArticuloAlmacenable *>(i->first))
    {
      if (i->second > art_almacenable->stock())
      {
        const_cast<Usuario::art &>(us.compra()).clear();
        throw SinStock(i->first);
      }
    }
    else
    {
      if (LibroDigital *libro_digital = dynamic_cast<LibroDigital *>(i->first))
      {
        if (libro_digital->f_expir() < f)
        {
          us.compra(*i->first, 0);
        }
      }
      if (us.compra().empty())
      {
        throw Vacio(&us);
      }
    }
  }

  u_p.asocia(*this, us);
  auto temporal = us.compra();
  for (auto i : temporal)
  {

    importe_total_ += i.first->precio() * i.second;
    p_a.pedir(*this, *i.first, i.first->precio(), i.second);
    if (ArticuloAlmacenable *art_almacenable = dynamic_cast<ArticuloAlmacenable *>(i.first))
    {
      art_almacenable->stock() -= i.second;
    }
    us.compra(*i.first, 0);
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
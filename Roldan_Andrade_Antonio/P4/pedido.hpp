#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"
#include <iomanip>
#include <iostream>
class Pedido_Articulo;
class Pedido
{
private:
    int numero_ped_;
    const Tarjeta *tarjeta_pago_;
    double importe_total_;
    Fecha fecha_pedido_;
    static unsigned n_ped_t_;

public:
    static unsigned n_total_pedidos()
    {
        return n_ped_t_;
    }

    Pedido(Usuario_Pedido &, Pedido_Articulo &, Usuario &, const Tarjeta &, const Fecha &f = Fecha()); // f= fecha actual

    class Vacio
    {
        Usuario *us_;

    public:
        Vacio(Usuario *us) : us_(us) {}
        Usuario &usuario() const { return *us_; }
    };

    class Impostor
    {
        Usuario *us_;

    public:
        Impostor(Usuario *us) : us_(us) {}
        Usuario &usuario() const { return *us_; }
    };

    class SinStock
    {
        Articulo *art_;

    public:
        SinStock(Articulo *art) : art_(art) {}
        Articulo &articulo() const { return *art_; }
    };

    const int numero() const noexcept
    {
        return numero_ped_;
    }
    const Tarjeta *tarjeta() const noexcept
    {
        return tarjeta_pago_;
    }
    const Fecha fecha() const noexcept
    {
        return fecha_pedido_;
    }
    const double total() const noexcept
    {
        return importe_total_;
    }
};
std::ostream &operator<<(std::ostream &salida, const Pedido &p);

#endif
#ifndef ARTICULO_H
#define ARTICULO_H

#include <string>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
using namespace std;
class Articulo
{
public:
	Articulo(const Cadena &referencia_, const Cadena &titulo__, const Fecha &f_,
			 const double &precio__, const size_t exs_ = 0)
		: codigo_referencia(Cadena(referencia_)), titulo_(Cadena(titulo__)), fecha_publicacion(f_), ejemplares_venta(exs_), precio_(precio__){};

	inline const char *referencia()
	{
		return codigo_referencia.c_str();
	}
	inline const Cadena titulo()
	{
		return titulo_;
	}

	inline const size_t stock() const
	{
		return ejemplares_venta;
	}
	inline size_t &stock()
	{
		return ejemplares_venta;
	}

	inline const double precio() const
	{
		return precio_;
	}
	inline double &precio()
	{
		return precio_;
	}

	inline const Fecha &f_publi()
	{
		return fecha_publicacion;
	}

	friend ostream &operator<<(std::ostream &salida, const Articulo &a) noexcept
	{
		salida << "[" << a.codigo_referencia << "]";
		salida << " "
				  ""
			   << a.titulo_ << ""
							   ", "
			   << a.fecha_publicacion.anno() << ". " << a.precio_ << " €";
		return salida;
	}

private:
	Cadena codigo_referencia;
	Cadena titulo_;
	Fecha fecha_publicacion;
	size_t ejemplares_venta;
	double precio_;
};

#endif
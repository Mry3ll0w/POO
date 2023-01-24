#ifndef ARTICULO_H
#define ARTICULO_H

#include <string>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <set>
#include <iomanip>
#include <set>
#include <stdlib.h>
#include <iostream>
#include <locale>
using namespace std;
class Autor
{
public:
	Autor(const Cadena &nom, const Cadena &ap, const Cadena &dir)
		: nom_(nom), ap_(ap), dir_(dir) {}

	const Cadena &nombre() const noexcept
	{
		return nom_;
	}
	const Cadena &apellidos() const noexcept
	{
		return ap_;
	}
	const Cadena &direccion() const noexcept
	{
		return dir_;
	}

private:
	Cadena nom_;
	Cadena ap_;
	Cadena dir_;
};

class Articulo
{
public:
	typedef std::set<Autor *> Autores;
	Articulo(const Autores &auts, const Cadena &ref_, const Cadena &titulo__, const Fecha &f_,
			 const double &precio__, const size_t exs_ = 0)
		: codigo_referencia(Cadena(ref_)), titulo_(Cadena(titulo__)), fecha_publicacion(f_), ejemplares_venta(exs_),
		  precio_(precio__), autores_(auts){};

	inline const Cadena referencia() const
	{
		return codigo_referencia;
	}
	inline const Cadena titulo() const
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

	inline const Fecha &f_publi() const
	{
		return fecha_publicacion;
	}
	inline const Autores &autores() const noexcept
	{
		return autores_;
	}
	friend ostream &operator<<(std::ostream &salida, const Articulo &a) noexcept
	{

		const auto autores = a.autores();
		auto i = autores.begin();
		std::locale::global(std::locale(""));

		salida << "[" << a.referencia() << "] \"" << a.titulo() << "\", de " << (*i)->apellidos();
		i++;
		for (; i != autores.end(); ++i)
		{
			salida << ", " << (*i)->apellidos();
		}

		salida << ". " << a.f_publi().anno() << ". ";
		salida << fixed << setprecision(2) << a.precio() << " €\n\t";

		a.impresion_especifica(salida);
		return salida;
	}

	virtual void impresion_especifica(std::ostream &salida) const = 0;
	virtual ~Articulo() {}
	class Autores_vacios
	{
	};

private:
	Cadena codigo_referencia;
	Cadena titulo_;
	Fecha fecha_publicacion;
	size_t ejemplares_venta;
	double precio_;
	const Autores autores_;
};

class LibroDigital : public Articulo
{
public:
	LibroDigital(const Autores &auts, const Cadena &ref_, const Cadena &titulo__, const Fecha &f_publi_, const double precio_, const Fecha &f_exp_) : Articulo(auts, ref_, titulo__, f_publi_, precio_), f_expir_(f_exp_) {}

	const Fecha f_expir() const noexcept
	{
		return f_expir_;
	}
	void impresion_especifica(std::ostream &salida) const
	{
		salida << "A la venta hasta el " << f_expir_ << ".";
	}

private:
	const Fecha f_expir_;
};

class ArticuloAlmacenable : public Articulo
{
public:
	ArticuloAlmacenable(const Autores &autores, const Cadena &ref_, const Cadena &titulo__, const Fecha &f_publi_,
						const double precio_, unsigned stock = 0)
		: Articulo(autores, ref_, titulo__, f_publi_, precio_), stock_(stock) {}

	const unsigned stock() const noexcept
	{
		return stock_;
	}
	unsigned &stock() noexcept
	{
		return stock_;
	}

protected:
	unsigned stock_;
};

class Libro : public ArticuloAlmacenable
{
private:
	const unsigned paginas;

public:
	Libro(const Autores &autores, const Cadena &ref_, const Cadena &titulo__, const Fecha &f_publi_, const double precio_, unsigned pgs_, unsigned stock = 0)
		: ArticuloAlmacenable(autores, ref_, titulo__, f_publi_, precio_, stock), paginas(pgs_) {}

	const unsigned n_pag() const noexcept
	{
		return paginas;
	}
	void impresion_especifica(std::ostream &salida) const
	{
		salida << paginas << " págs., " << stock_ << " unidades.";
	}
};

class Cederron : public ArticuloAlmacenable
{
public:
	Cederron(const Autores &auts, const Cadena &ref_, const Cadena &titulo__, const Fecha &f_publi_,
			 const double precio_, unsigned size__, unsigned stock = 0)
		: ArticuloAlmacenable(auts, ref_, titulo__, f_publi_, precio_, stock), size_(size__) {}

	const unsigned tam() const noexcept
	{
		return size_;
	}
	void impresion_especifica(std::ostream &salida) const
	{
		salida << size_ << " MB, " << stock_ << " unidades.";
	}

private:
	const unsigned size_;
};

#endif
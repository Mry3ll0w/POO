#ifndef ARTICULO_H
#define ARTICULO_H

#include <string>
#include "cadena.hpp"
#include "fecha.hpp"
using namespace std;
class Articulo
{
public:
	Articulo(const char* referencia_,const char* titulo__,const char* f_,
	const double& precio__, const size_t exs_=0 )
	:codigo_referencia(Cadena(referencia_)),titulo_(Cadena(titulo__)),fecha_publicacion(f_),precio_(precio__),ejemplares_venta(exs_){
	};
	//~Articulo(); no es necesario ya que Cad tiene destructor y fecha tambien
	inline const char* referencia(){return codigo_referencia.c_str();}
	inline const char* titulo(){return titulo_.c_str();}

	inline const size_t stock()const{return ejemplares_venta;}
	inline size_t& stock(){return ejemplares_venta;}

	inline const double precio()const{return precio_;}
	inline double& precio(){return precio_;}

	friend ostream& operator<<(std::ostream& salida,const Articulo& a)noexcept{
    	salida<<"["<<a.codigo_referencia<<"]";
		salida<<" """<<a.titulo_<<""", "<<a.fecha_publicacion.anno()<<". "<<a.precio_<<" €";
    	return salida;
	}

private:
	Cadena codigo_referencia;//Sin restricciones
	Cadena titulo_;
	Fecha fecha_publicacion;
	size_t ejemplares_venta;
	double precio_;
};

#endif
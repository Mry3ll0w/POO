#ifndef TARJETA_H
#define TARJETA_H
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <set>
class Usuario;
class Numero
{
public:
	//CONSTRUCTORES
	Numero(const char* n);
	const char* numero()const{return numero_.c_str();}
	operator const char*()const{return numero_.c_str();}
	//Excepciones
	enum Razon{LONGITUD,DIGITOS,NO_VALIDO};

    /**
     * Clase incorrecto para el manejo de excepciones
     * */
    class Incorrecto
    {
    private:
        Razon r;
    public:
        Incorrecto(const Razon r_):r(r_){};
        Razon razon()const{return r;}   
    };

private:
	Cadena numero_;
};








/* ------------------------------ CLASE TARJETA ----------------------------- */

class Tarjeta
{
public:

    enum Tipo{Otro,VISA,Mastercard,Maestro,JCB,AmericanExpress};
	
    Tarjeta(const Numero& numero, Usuario& user,const Fecha& fecha_caducidad);
    Tarjeta(const Tarjeta& that)=delete;
    Tarjeta& operator=(const Tarjeta&)=delete;
    ~Tarjeta();

    const Fecha cuando ()const{return caducidad_;}
    void anular_titular(){const_cast<Usuario*&>(titular_) =nullptr; activa_=false;}
    void no_es_titular(){anular_titular();}//Solicitada por el enunciado, aunque anular titular lo hace 
/* ------------------- Clases para el manejo de excepciones ------------------ */
    class Caducada
    {
    private:
        Fecha f_caducada;
    public:
        Caducada(const Fecha& f_):f_caducada(f_){};
        const Fecha cuando()const {return f_caducada;}   
    };

    class Num_duplicado{
        public:
            Num_duplicado(const Numero& n_):n(n_){};
            const Numero que()const{return n;}
        private:
            Numero n;
    };

    class Desactivada{
        private:
        public:
            Desactivada(){}
    };

    
   
/* ------------------------------ observadores ------------------------------ */
    const Numero& numero()const{return numero_;}
    const Usuario* titular()const{ return titular_; }
    const Fecha& caducidad()const{ return caducidad_;}
    const bool activa()const{return activa_;}
    bool activa(bool f){return activa_;}
    const Tipo& tipo()const;
   // const Tarjeta::Tipo tipo()const{return tipo_;}


private:
    Numero numero_;
    Usuario* titular_;
    Fecha caducidad_;
    bool activa_;
    std::set<Numero*>Tarjetas;
    Tipo tipo_;
};

bool alg_luhn(const char *numero);
bool operator <(const Numero&, const Numero&);
bool operator < (const Tarjeta& a, const Tarjeta& b);
/* ------------------ SOBRECARGA DEL OPERADOR DE INSERCION ------------------ */
ostream& operator<<(std::ostream& salida,const Tarjeta& a)noexcept;
#endif
#ifndef TARJETA_H
#define TARJETA_H
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <set>
class Usuario;
class Numero{
public:
	//CONSTRUCTORES
	Numero(const Cadena& n);
	
/* ------------------------------- constantes ------------------------------- */
    enum Razon{LONGITUD,DIGITOS,NO_VALIDO};
/* --------------------------------- METODOS -------------------------------- */
    const char* n()const{return numero_.c_str();}
	operator const char*()const;
    Cadena espacio(const Cadena& cad);
    Cadena longitud(const Cadena& cad);
	

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
    typedef  std::set<Numero> num;
    enum Tipo{Otro,VISA,Mastercard,Maestro,JCB,AmericanExpress};
	
    Tarjeta(const Numero& numero, Usuario& user,const Fecha& fecha_caducidad);
    Tarjeta(const Tarjeta& that)=delete;
    Tarjeta& operator=(const Tarjeta&)=delete;
    ~Tarjeta();

    const Fecha cuando ()const{return caducidad_;}
    void anula_titular(){titular_ = nullptr;activa_=false;}
    
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
    };
    
    
   
/* ------------------------------ observadores ------------------------------ */
    Numero numero()const{return numero_;}
    const Usuario* titular()const{ return titular_; }
    Fecha caducidad()const{ return caducidad_;}
    bool activa()const{return activa_;}
    bool activa(bool f);
    Tipo tipo()const{return tipo_;}
    Tarjeta::Tipo selec_tipo()const;

private:
    Numero numero_;
    const Usuario* titular_;
    Fecha caducidad_;
    bool activa_;
    Tipo tipo_;
    static std::set<Numero> numeros;
};

bool operator <(const Numero&, const Numero&);
bool operator < (const Tarjeta& a, const Tarjeta& b);
/* ------------------ SOBRECARGA DEL OPERADOR DE INSERCION ------------------ */
ostream& operator<<(std::ostream& salida,const Tarjeta& a)noexcept;
ostream& operator<<(std::ostream& salida,const Tarjeta::Tipo a)noexcept;
#endif
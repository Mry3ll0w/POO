#include "tarjeta.hpp"
#include <iomanip> 
#include <cstring> 
#include <string.h> 
#include <cctype>
#include "usuario.hpp"
bool luhn(const Cadena& num);
/* ------------------------------ Clase numero ------------------------------ */

Numero::Numero(const char* n)
	: numero_(Cadena(n))
{
    //EXCEPCION LONGITUD
    if (numero_.length()<13||numero_.length()>19)
    {
        throw Incorrecto(Razon::LONGITUD);
    }
    //EXCEPCION NO_VALIDO
    if (!luhn(numero_.c_str()))
    {
        //throw Incorrecto(Razon::NO_VALIDO);
    }
    
    
    //Construccion de la cadena de digitos
	char claves[]="./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    size_t aux_s = strcspn(numero_.c_str(),claves);
    if (aux_s<numero_.length()) 
    {
        throw Incorrecto(Razon(DIGITOS));

    }
    size_t i;
    char* aux_cad;
    char* aux = new char[30];
    aux_cad = strpbrk(const_cast <char*>(numero_.c_str()),"1234567890");
    for ( i = 0; aux_cad !=NULL; i++)
    {
        aux[++i]=*aux_cad;
        aux_cad = strpbrk(aux_cad+1,"1234567890");
    }
    aux[i]='\0';
    numero_=aux;
    delete[] aux;

}


bool operator <(const Numero& a, const Numero& b) {
	return strcmp(a,b)<0;
}

/* ------------------------------ clase tarjeta ----------------------------- */


Tarjeta::Tarjeta(const Numero& numero, Usuario& user,const Fecha& fecha_caducidad)
    : numero_(numero),
      titular_(&user),
      caducidad_(fecha_caducidad),
      activa_(true),
      tipo_(tipo())
{

/* ------------------------ La tarjeta esta duplicada ----------------------- */

    if (Tarjetas.insert(&numero_).second==false)
    {
        throw Tarjeta::Num_duplicado(numero_);
    }
    
/* ------------------------- La tarjeta esta Caducada ------------------------ */
    if (caducidad_ >=Fecha())//Si la fecha de caducidad es mayor o igual que la actual entonces esta caducada
    {
        //throw Caducada(fecha_caducidad);
        /* -------------------------------- ARREGLAR -------------------------------- */

    }

}

const Tarjeta::Tipo Tarjeta::tipo()const{
    Cadena aux_tipo =numero_.numero();
    if (aux_tipo[0]=='3')
    {
        if (aux_tipo[1]=='4'||aux_tipo[1]=='7')
        {
            return AmericanExpress;
        }
        else{
            return JCB;
        } 
    }
    else if(aux_tipo[0]=='4'){
        return VISA;
    }
    else if(aux_tipo[0]=='5'){
        return Mastercard;
    }
    else if (aux_tipo[0]=='6')
    {
        return Maestro;
    }
    else
        return Otro;
}

Tarjeta::~Tarjeta()
{
    if(titular_) titular_->no_es_titular_de(*this);
}

ostream& operator<<(std::ostream& salida,const Tarjeta& a)noexcept{
    switch(a.tipo()){ 
        case Tarjeta::VISA: salida << "VISA"; break;
        case Tarjeta::Mastercard: salida << "Mastercard"; break; 
        case Tarjeta::Maestro: salida << "Maestro"; break; 
        case Tarjeta::JCB:salida << "JCB"; break; 
        case Tarjeta::AmericanExpress: salida << "AmericanExpress"; break; 
        case Tarjeta::Otro: salida << "Otro"; break;  
    }
    return salida;
}

bool operator < (const Tarjeta& a, const Tarjeta& b){
    return a.numero()<b.numero();
}

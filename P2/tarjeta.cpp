#include "tarjeta.hpp"
#include "usuario.hpp"
/* ----------------- Algoritmo de luhn para la verificacion ----------------- */

bool alg_luhn(const char *numero) {
    char *n;
    int digito;
    bool par = false;
    int res = 0;

    n = new char[strlen(numero)+1];
    strcpy(n, numero);
    do {
        digito = n[strlen(n)-1]-'0';
        n[strlen(n)-1] = 0;
        res += digito;
        if(par) {
            res += digito;
            if(digito > 4) res -= 9;
        }
        par = !par;

    } while(strlen(n));
    delete[] n;
    return !(res % 10);
}


/* ------------------------------ Clase numero ------------------------------ */

Numero::Numero(const char* n)
	: numero_(Cadena(n))
{
    //EXCEPCION LONGITUD
    if (numero_.length()<13||numero_.length()>19)
    {
        throw Incorrecto(Razon(LONGITUD));
    }
    //EXCEPCION NO_VALIDO
    if (!alg_luhn(numero_.c_str()))
    {
        throw Incorrecto(Razon(NO_VALIDO));
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
      activa_(true)
{

/* ------------------------ La tarjeta esta duplicada ----------------------- */

    if (Tarjetas.insert(this).second==false)
    {
        throw Tarjeta::Num_duplicado(numero_);
    }
    
/* ------------------------- La tarjeta esta Caducada ------------------------ */
    if (caducidad_ >=Fecha())//Si la fecha de caducidad es mayor o igual que la actual entonces esta caducada
    {
        throw Tarjeta::Caducada(caducidad_);
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

ostream& operator<<(std::ostream& salida,const Tarjeta& a)noexcept{
    salida<<a.tipo()<<endl;
    salida<<a.numero().numero()<<endl;
    salida<<a.titular()->nombre().c_str()<<" "<<a.titular()->apellidos().c_str()<<endl;
    salida<<"Caduca: "<<a.caducidad().mes()<<"/"<<a.caducidad().anno()<<endl;
    return salida;
}


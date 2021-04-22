#include "tarjeta.hpp"
/////////////////////////////////////Alogritmo de LUHN///////////////////////
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


/////////////////////Clase NUMERO//////////////////////////
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

#include "usuario.hpp"
#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include <random>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <unistd.h>

using namespace std;

/* ------------------------------- CLASE CLAVE ------------------------------ */

Clave::Clave(const char* input){
    //Excepcion de clave demasiado corta

/* -------------------------------- ARREGLAR -------------------------------- */

    if (strlen(input)<5){ throw Incorrecta(Razon::CORTA);} 
    //Encriptado    
    char const MD5chars[]="./0123456789ABCDEFGHIJKLMNOPQRST"
    "UVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device r_dev;
    char salida[2]={MD5chars[rand() % 64],MD5chars[rand()% 64]};

    if (crypt(input,salida)==nullptr)
    {
        throw Clave::ERROR_CRYPT;
    }
    clave_cifrada =crypt(input,salida);
} 


bool Clave::verifica(const char* a)const{
    Cadena v(crypt(a,clave_cifrada.c_str()));
    return v == clave_cifrada;
}


/* ------------------------------ CLASE USUARIO ----------------------------- */


Usuario::Usuario(const Cadena& id,const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& clave)
    : identficador_(id),
      nombre_(nombre),
      apellidos_(apellidos),
      direccion_(direccion),
      pass_(clave)
{
    if (identificadores.insert(&identficador_).second==false)
	{
		throw Id_duplicado(identficador_);//Este user ya existe
	}
    
}

void Usuario::es_titular_de(Tarjeta& t) {
    if (t.activa()==false)
    {
        throw Tarjeta::Desactivada();
    }
    
    if (t.titular()==this)//Compara la direccion de memoria directamente
    {
        Tarjeta_.insert(make_pair(t.numero(),&t));
    }
}

Usuario::~Usuario()
{
    for (auto i:Tarjeta_)
    {
        i.second->anular_titular();
    }
    identificadores.erase(&identficador_);//elimina user de la lista
}



void Usuario::no_es_titular_de(Tarjeta& t) {
    Tarjeta_.erase(t.numero());//Elimina la tarjeta del set de tarjetas
}

void Usuario::compra(Articulo& a, unsigned int cantidad) {
    auto found = Articulos.find(&a);
    if (found!=Articulos.end())//Si el articulo esta en el carrito y cantidad == 0 eliminalo 
    {
        if (cantidad==0)
        {
            Articulos.erase(Articulos.find(&a));
        }
        if(cantidad>0){
           found->second=cantidad;
        }
       
    }
    else{
        Articulos.insert(make_pair(&a,cantidad));
    }
}

void mostrar_carro(ostream& salida,Usuario& u) {
    salida<<"Carrito de compra de "<<u.id()<<'['<<u.n_articulos()<<']'<<endl;
    salida<<"=============================================================="<<endl;
    for (auto i=u.compra().begin();i!=u.compra().end();++i)
    {
        salida<<i->second<<"\t"<<i->first<<endl;
    }

}

ostream& operator<<(std::ostream& salida,const Usuario& a)noexcept {
    salida<<a.id()<<'['<<a.pass_.clave().c_str()<<']'<<" "<<a.nombre()<<" "<<a.apellidos()<<endl;
    salida<<a.direccion()<<endl;
    for (auto i:a.Tarjeta_)
    {
        salida<<i.second<<endl;
    }
    return salida;
}





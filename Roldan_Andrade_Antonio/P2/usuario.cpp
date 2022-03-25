#include "usuario.hpp"
#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include <unistd.h> 
#include <cstdlib> 
#include <string.h> 
#include <random> 
#include <iomanip> 
#include <set>

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
Usuario::I Usuario::identificadores;

Usuario::Usuario(const Cadena& id,const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& clave)
    : identficador_(id),
      nombre_(nombre),
      apellidos_(apellidos),
      direccion_(direccion),
      pass_(clave)
{
    if (identificadores.insert(identficador_).second==false)
	{
		throw Id_duplicado(identficador_);//Este user ya existe
	}
    
}

void Usuario::es_titular_de(Tarjeta& t) {
   
    if (t.titular()==this)//Compara la direccion de memoria directamente
    {
        Tarjeta_.insert(make_pair(t.numero(),&t));
    }
    
}

Usuario::~Usuario()
{
    for ( Usuario::Tarjetas::const_iterator i=Tarjeta_.begin();i!=Tarjeta_.end();++i)
    {
        i->second->anula_titular();
    }
    identificadores.erase(identficador_);
    //identificadores.//elimina user de la lista
}


void Usuario::compra(Articulo& a, unsigned int cantidad) {
    auto found = Articulos.find(&a);
    if (found == Articulos.end() ){ 
        if(cantidad > 0){ 
        Articulos[const_cast<Articulo*>(&a)] = cantidad; 
 
        } 
    }else{ 
            if(cantidad > 0 ){ 
            Articulos[const_cast<Articulo*>(&a)] = cantidad; 
            }   
            else{ 
            Articulos.erase(const_cast<Articulo*>(&a)); 
            } 
    } 
    
}

void mostrar_carro(ostream& salida,Usuario& u) {
    salida<<"Carrito de compra de "<<u.id()<<" [Artículos: "<<u.n_articulos()<<"]"<< endl<< " Cant.\tArtículo" <<endl; 
    salida <<"===========================================================" <<endl; 
    for(auto i = u.compra().begin(); i != u.compra().end(); ++i){ 
        salida << " " << i->second << "\t" << "[" << i->first->referencia() << "] \"" << i->first->titulo() << "\", "; 
        salida << i->first->f_publi().anno() << ". " << setprecision(2) << std::fixed << i->first->precio() << " €" << endl;
    } 

}

ostream& operator<<(std::ostream& salida,const Usuario& a)noexcept {
    salida<<a.id()<<'['<<a.pass_.clave()<<']'<<" "<<a.nombre()<<" "<<a.apellidos()<<endl;
    salida<<a.direccion()<<endl;
    salida<<"Tarjetas: "<<endl;
    for (Usuario::Tarjetas::const_iterator i=a.Tarjeta_.begin();i!=a.Tarjeta_.end();++i)
    {
        salida<<*(i->second)<<endl;
    }
    return salida;
}

void Usuario::no_es_titular_de(Tarjeta& t){
    t.anula_titular();
    Tarjeta_.erase(t.numero());
}



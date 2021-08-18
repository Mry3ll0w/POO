#include <iostream>
#include <string>
class Cadena{
    char* pc; /* Contiene la cadena */
    size_t n;  /* Indica el tamaño de la cadena  */
public:
    
    Cadena(size_t n_=1);//a) ctor cree cadena con espacio n caracteres
    Cadena(const char*);
    size_t get_n()const{return n;}
    Cadena& operator=(const Cadena&);
    void cad_show(){
        for (size_t i = 0; i < n; i++)
        {
            std::cout<<pc[i];
        }
        std::cout<<std::endl;
    }
    ~Cadena(){
        delete [] pc;
    }
    char& operator[](size_t i);

};
Cadena operator +(Cadena& a,Cadena& b){
    Cadena dest(a.get_n()+b.get_n());
    size_t it=0;
    for (size_t i = 0; i < a.get_n(); i++)
    {
        dest[it]=a[i];++it;
    }
    for (size_t i = 0; i < b.get_n(); i++)
    {
        dest[it]=b[i];++it;
    }
    return dest;
}
std::ostream& operator<<(std::ostream& os,  Cadena& c){
    for (size_t i = 0; i < c.get_n(); i++)
    {
        os<<c[i];
    }
    return os;
}
/* ---------------------------- MAIN PARA PRUEBAS --------------------------- */
int main(){ 
    /* Ejercicio 1 (pregunta de teoria)
        Defina los principios de encapsulado y ocultaci´on de datos de la programacion orientada a 
        objetos. 
        ¿Como influyen en la cohesion y el acoplamiento de los componentes de un sistema?
    */
    Cadena c("string"),d("str"),e;
    e=c+d;
    std::cout<<c<<std::endl;

}
/* ---------------------------- FUNCIONES Y DEMAS --------------------------- */
Cadena::Cadena(size_t n_)
    : n(n_)
{
    pc = new char[n];
    for (size_t i = 0; i < n; ++i)
    {
        pc[i]='#'; // el enunciado dice espacios pero es mas claro asi
    }
        
}

Cadena::Cadena(const char* input){
    /* Primero obtenemos el tamaño del input */
    size_t i=0;
    while (input[i]!='\0')
    {
        ++i;
    }
    n=i+1;
    pc = new char[i+1];//Ya que tiene la cadena mas el caracter terminador
    for(i=0; i < n; ++i){
        pc[i] = input[i];
    }

}

Cadena& Cadena::operator =(const Cadena& c){
    n=c.n;
    delete [] pc;
    pc= new char[n];

    for (size_t i = 0; i < n; i++)
    {
        pc[i]=c.pc[i];
    }
    return *this;
}

char& Cadena::operator[](size_t i){
    if (i<0 || i>=n)
    {
        throw std::out_of_range("Character out of range");
    }
    return pc[i];
}
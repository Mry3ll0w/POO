#include<vector>
#include <string>
#include<iostream>
#include <bits/stdc++.h> // para el set intersection
/* ------------------------------- EJERCICIO 2 ------------------------------ */
//clase de excepcion requerida por apartado b
class AccesoIndebido{};
class ADN{
    char *pc;
    size_t len;
public:
    ADN(size_t n=1):len(n),pc(new char[len]){}
    ADN(const char * input);
    char& operator[](size_t n);
    ADN& operator+=(ADN& a);
    ADN(ADN& a);//necesario para la sobrecarga del operador de insercion
};
ADN::ADN(ADN& a){
    len = a.len;
    delete [] pc;
    pc = new char[len+1];
    for (size_t i = 0; i < len; i++)
    {
        pc[i]=a.pc[i];
    }
}
ADN::ADN(const char * input){
    size_t n = 0;
    //obtenemos el tamaño de la cadena de adn introducida
    while(input[n] != '\0'){//A C G T
        if(input[n] != 'A' && input[n] != 'C' && input[n] != 'G'&& input[n] != 'T')
            throw std::runtime_error("La cadena de adn introducida tiene elementos erroneos");
        ++n;
    }
    len = n;
    //Si no se lanza la excepcion copiamos las cadena de ADN
    pc = new char[len+1];
    for(n=0;n<len;++n){
        pc[n] = input[n];
    }
}
char& ADN::operator[](size_t n){
    if(n<=0||n>=len)
        throw AccesoIndebido();
    return pc[n];
}
ADN& ADN::operator+=(ADN& a){
    //creamos un vector para hacer la copia mas tarde
    std::vector<char> v;
    //copiamos el ADN de this
    for (size_t i = 0; i < len; i++)
    {
        v.insert(v.end(),pc[i]);
    }
    //copiamos el ADN de a
    for (size_t i = 0; i < a.len; i++)
    {
        v.insert(v.end(),a.pc[i]);
    }
    //borramos el puntero pc para la posterior copia
    delete [] pc;
    pc = new char[v.size()+1];
    size_t it=0;
    for(auto i:v){ 
        pc[it]=i;
        ++it;
    }
    return *this;
}
std::istream& operator >>(std::istream& is, ADN& adn){
    std::string str;
    is>>str;
    adn=ADN(str.c_str());
    return is;
}
/* -------- EJERCICIO 4 (EL 3 ES EL DE LA CIRCUNFERENCIA Y EL ELIPSE) ------- */
//Recibe 2 conjuntos y devuelve un bool(saber si es disjunto), y pasa por referencia la interseccion
template <class t>
bool disjuntos(std::vector<t>& a, std::vector<t>&b,std::vector<t>& inter ){
    
    for (size_t i:a)
    {
        for(size_t j:b){

            if (i == j)
            {
                inter.insert(inter.end(),j);
            }
            
        }
    }
    
    return inter.size()== 0;
}
template <class t>
std::ostream& operator <<(std::ostream&os,std::vector<t>&v){
    for (size_t i:v)
    {
        os<<v[i]<<", ";
    }
    return os;
}
//faltan la funcion comparten 
/* ---------------------------- MAIN PARA PRUEBAS --------------------------- */
int main(){
    std::vector<int> a,b,c;

    
    
}
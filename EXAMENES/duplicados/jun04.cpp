#include <iostream>
#include <string>
#include <cstring>
using namespace std;//Avoid using std:: ....
//EJERCICIO 1
class cadena{
    size_t tam;
    char* str;
public:
    class AccesoIndebido{};//CLase de excepcion
    cadena(const char* str);
    cadena(const size_t );
    cadena& operator=(const char*);
    cadena(cadena& a);
    const size_t tam_(){return tam;}
    const char* c_str() const{return str;}
    //~cadena(){delete[] str;}
    char& operator[](size_t);
    const char& operator[](size_t) const;
    cadena& operator +=(cadena& a);
    friend ostream& operator<<(ostream&os,cadena&a){
        os<<a.c_str();
        return os;
    }
};
/* -------------------------- MAIN PARA IMPLEMENTAR ------------------------- */
int main(){
    cadena a("Scum"),b("bag");
    cout<<a<<endl;
    return 0;
}
/* -------------------------- METODOS DE LAS CLASES ------------------------- */
cadena operator + (cadena& a,cadena& b){
    char* temp = new char[a.tam_()+ b.tam_()+1];
    strcpy(temp,a.c_str());
    strcat(temp,b.c_str());
    cadena t(temp);
    delete []temp;
    return t;
}
char& cadena::operator[](size_t i){
    if (i<0 || i>=tam)
    {
        throw AccesoIndebido();
    }
    return str[i];
    
}
const char& cadena::operator[](size_t i)const{
    if (i<0 || i>=tam)
    {
        throw AccesoIndebido();
    }
    return str[i];
}
cadena& cadena::operator=(const char* a){
    cout<<"operador ="<<endl;
    delete []str;
    tam=0;//Borramos el tamaño de la cadena antigua
    while(a[++tam] != '\0');     
    str = new char[tam+1];
    for (size_t i = 0; i < tam; i++)
    {
        str[i]=a[i];
    }
    return *this;
    
}

cadena::cadena(const char* input){
    while (input[++tam]!='\0');
    str = new char[tam];
    for (size_t i = 0; i < tam; i++)
    {
        str[i] = input[i];
    }
}
cadena::cadena(const size_t n=1):tam(n),str(new char[n+1]){
    for (size_t i = 0; i < tam; i++)
    {
        str[i] = '#';
    }
}
cadena::cadena(cadena& a){
    cout<<"ctor de conversion"<<endl;
    tam = a.tam;
    str = new char[tam+1];
    
    for (size_t i = 0; i < a.tam; i++)
    {
        str[i] = a.str[i];
    }
}
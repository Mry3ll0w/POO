#include<iostream>
#include<string>
#include<vector>
#define bits_elto 16
class binario{
    unsigned* v;
    size_t m; //m = (n+bits_elto-1)/bits_elto
    unsigned int n;// size vector
    bool check(const char*);
public:
    bool bit(size_t i){
        if(i<0 || i>=n){
            throw std::out_of_range("fallo indice");
        }
        return v[i]==1;
    }
    explicit binario(size_t);
    const size_t n_bits()const{return n;}
    const size_t unos()const;
    binario(const char* v);
    void show(){
        for(size_t i = 0; i < n; i++)
        {
            std::cout << v[i];
        }
        std::cout<<std::endl;
    }
    const unsigned* vector()const;
    unsigned* vector();
    unsigned& operator[] (size_t i);
    binario& operator = (binario& b);
    friend std::ostream& operator<<(std::ostream& os , const binario& a){
        os<<"El numero tiene "<<a.unos()<<" con valor 1 y "<<a.n_bits()-a.unos()<<" con valor 0";
        return os;
    }
};

int main(){
    binario a("010101");
    std::cout << a << std::endl;
}
/* --------------------------------- METODOS -------------------------------- */
binario& binario::operator =(binario& b){
    delete [] v;
    n = b.n_bits();
    v = new unsigned[n];
    for (size_t i = 0; i < n; i++)
    {
        v[i]=b.v[i];
    }
    return *this;
}
bool binario::check(const char* s){
    bool token;
    token = true;
    for (size_t i = 0; s[i] != '\0'; i++)
    {
        if (s[i]==1||s[i]==0)
        {
            token = false;
        }
            
    }
    return token;
}
unsigned& binario::operator[] (size_t i){
    if (i<0 || i>=n)
    {
        throw std::out_of_range("indice incorrecto");
    }
    return v[i];
}
unsigned* binario::vector(){
    return v;
}
const unsigned* binario::vector()const{
    return v;
}

const size_t binario::unos()const{
    size_t cont=0;
    for (size_t i = 0; i < n; i++)
    {
        if (v[i]==1)
        {
            cont++;
        }
    }
    return cont;
}
binario::binario(size_t n_=1):n(n_),v(new unsigned[n]){
    for (size_t i = 0; i < n; i++)
    {
        v[i]=0;
    }
}

binario::binario(const char* v_){
    if (!check(v_))
    {
        throw std::runtime_error("Se ha introducido algo distinto de 0 o 1");
    }
    size_t tam = 0;
    for (size_t i = 0; v_[i]!='\0'; i++)
    {
        tam++;
    }
    n=tam;
    v = new unsigned[n];
    for (size_t i = 0; i < n; i++)
    {
        if (v_[i]=='0')
        {
            v[i]=0;
        }
        else{
            v[i]=1;
        }
    }
}

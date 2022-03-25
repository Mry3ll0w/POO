#include<iostream>
#include<string>
#include<initializer_list>
class Vector{
    size_t n;
    double* datos;
public:
    Vector(size_t n_,double);
    Vector(const std::initializer_list<double>&l);
    void show();
    ~Vector(){
        delete[] datos;
    }
    Vector(Vector&& other):n(other.n){
        delete [] datos;
        datos =other.datos;
        other.datos =nullptr;
    }
    Vector(const Vector& v);
    Vector operator = (const Vector& v);
    const double at(size_t i)const;
};
/* --------------------------- METODOS DE LA CLASE -------------------------- */
const double Vector::at(size_t i)const{
    if (i<0 || i>=n)
    {
        throw std::out_of_range("ese indice es invalido");
    }
    return datos[i];
}

Vector::Vector(const Vector&v){
    n=v.n;
    datos = new double[n];
    
    for (size_t i = 0; i < n; i++)
    {
        datos[i] = v.datos[i];
    }
    std::cout<<std::endl;
    
}
Vector Vector::operator = (const Vector& v){
    //delete [] datos;
    n = v.n;
    for (size_t i = 0; i < n; i++)
    {
        datos[i] = v.datos[i];
    }
    return *this;
}
Vector::Vector(const std::initializer_list<double>&l):n(l.size()),datos(new double[n]){
    size_t j= 0;
    for (auto i:l)
    {
        datos[j]=i;
        ++j;
    }
}

void Vector::show(){
    for (size_t i = 0; i < n; i++)
    {
        std::cout<<datos[i]<<", ";
    }
    std::cout<<std::endl;
}
Vector::Vector(size_t n_,double d=0):n(n_),datos(new double[n]){
    if (n < 1)
    {
        throw std::invalid_argument("Wrong size!");
    }
    
    for (size_t i = 0; i < n; i++)
    {
        datos[i] = d;
    }
}
int main(){
    Vector a={2,3,4,5,6};
    std::cout<<a.at(3)<<std::endl;
    return 0;
}
#include <iostream>
using namespace std;//Avoid using std:: ....

/* Primer ejercicio */
class Vector{
    public:
        Vector(size_t tam, double e=0):n(tam){
            datos = new double[tam];
            for (size_t i = 0; i < tam; i++)
            {
                datos[i]=e;
            }
        }
        Vector(const std::initializer_list<double&>list){
            n = list.size();
            size_t j=0;
            for(auto i:list){
                datos[j]=*i;
                ++j;
            }
            
        }
        size_t n_get(){return n;}
        double* datos_get(){return datos;}
        Vector(Vector& v):n(v.n_get()){
            delete []datos;
            datos = new double[n];
            for (size_t i = 0; i < n; i++)
            {
                datos[i]=v.datos[i];
            }
        }
        Vector(Vector&& v):n(v.n_get()),datos(v.datos_get()){
            v.datos=0;
            v.n=0;
        }
        double at(size_t i){
            if (i<0 || i>=n)
            {
                throw std::out_of_range("fuera de rango");
            }
            return datos[i];
            
        }
    private:
        size_t n;
        double* datos;
};

/* Ejercicio 2 
    Basicamente para hacer lo pedido en el enunciado
    necesita de tener una sobrecarga del operador double
*/
class doble{
    private:
        double d;
    public:
        doble(double d_):d(d_){}
        operator double(){return d;}
        doble& operator = (doble& d_){
            d = d_.d;
            return *this;
        }
            
        
};

int main(){
    
    return 0;
}
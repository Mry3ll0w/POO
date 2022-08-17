#include <iostream>
#include <vector>

using namespace std;//Avoid using std:: ....

class Vector{
    size_t n;
    double *datos;
public:

    explicit Vector(size_t s, const double& e=0.0){
        if(s <= 0)
            throw invalid_argument("S tiene que ser > 0");
        n = s;
        datos = new double[s];

        for(size_t i = 0; i < s; ++i){
            datos[i] = e;
        }

    }

    Vector(initializer_list<double> l):datos(new double[l.size()]){
        size_t it = 0;
        n = l.size();
        for(auto i : l ){
            datos[it] = i;
            it++;
        }
    }

    ~Vector(){
        delete[]datos;
    }

    const size_t size()const {return n;}
    void imprime_vector(){
        cout << "Valor de n"<<size()<<endl;
        for (int i = 0; i < size(); i++)
        {
            cout << datos[i] << ", ";
        }

        cout<<endl;
    }

    //Ctor copia
    Vector(Vector& v){
        
        n = v.n;
        delete []datos;
        datos = new double[v.n];

        //Copiamos todos los datos de this a v
        for(size_t i = 0 ; i < n ; ++i){
            datos[i] = v.datos[i];
        }
        
    }

    //ctor movimiento 
    Vector(Vector&& v){
        n = v.n;
        datos = v.datos;
        v.datos = nullptr;

    }

    const double& at(size_t i )const {
        if(i < 0 || i > n)
            throw invalid_argument("i no valida");
        return datos[i];
    }

    double& at(size_t i){
        if (i < 0 || i > n)
            throw invalid_argument("i no valida");
        return datos[i];
    }

};



int main(){
    Vector v={1,23,4,51,2313.2},v2(3);
    cout << v.at(1231)<<endl;
    v.imprime_vector();
return 0;
}

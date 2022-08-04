#include <iostream>
#include <vector>

using namespace std;//Avoid using std:: ....

template<class T> 
class MatrizTriangularSuperior {
    size_t n;
    vector<T> v;
public:
    
    MatrizTriangularSuperior(size_t n= 1): n(n), v(n*(n-1)/2){}
    
    //Entiendo que hace las veces de m[i][j]
    T& operator()(size_t i, size_t j){
        
        if(i >= n || j >= n)
            throw out_of_range("n demasiado grande");
        
        if(i <= j)
            return v[i * (2+n-i+1)/2 +j -i];
        
    }

    size_t orden()const {return n;}

};

//¿Como definirias la clase MatrizSimetrica?
/*
    La defino como composición de la clase MatrizTriangularSuperior, ya que se necesitan
    todas las operaciones y atributos de la clase base para que esta tenga sentido.
*/

template <class T>
class MatrizSimetrica : public MatrizTriangularSuperior<T>{
    
public:

    MatrizSimetrica(const size_t n = 1):MatrizTriangularSuperior<T>(n){
        if(n < 1 )
            throw invalid_argument("N incorrecta");
    }


};

template<class T>
class MatrizCuadrada :public MatrizTriangularSuperior<T>{

public:
    MatrizCuadrada(const size_t n):MatrizTriangularSuperior<T>(n){}
    
}; 


//Funcion rellenar
template<class T>
void rellenar(MatrizTriangularSuperior<T>& m, int f = [&](){
    int sum = 0;
    for(size_t i = 0; i < m.orden(); ++i)
        for(size_t j = 0; j < m.orden(); ++j)
            sum += m(i,j);
    return sum;
})
{
    for(size_t i = 0; i < m.orden(); ++i)
        for(size_t j = 0; j < m.orden(); ++j)
            m(i,j) = f;
}



int main(){
    MatrizTriangularSuperior<int> m(3);
    MatrizSimetrica <int> s(3);
    MatrizCuadrada <int> mc(2);
    cout << s(0,0) << endl;
    std::cout<< m(0,0)<<endl;
    rellenar(s);
    rellenar(m);
    rellenar(mc);
return 0;
}


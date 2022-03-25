#include <iostream>
using namespace std;//Avoid using std:: ....
/**
 *   COSAS QUE TIENEN QUE COMPILAR
 *   Vector v1(5, 1.2); //v1 = {1.2, 1.2, 1.2, 1.2, 1.2}
 *   Vector v2(4); //v2={0, 0, 0, 0}
 *   Vector v3; //error de compilación
 *   Vector v4=3; //error de compilación IMPLICA EXPLICIT
 *   Vector v5={1,2.5,3}; //v5={1,2.5,3}
 *
 *   f) Implemente el método Vector::at para acceder a un elemento mediante su índice, de tal forma que
     el siguiente fragmento de código se ejecute correctamente y produzca la salida Vector::at, índice 
     fuera de rango. 2p
     const Vector v6={1,2,3,4,5,6};
     Vector v7(6);
     try{
          v7.at(0)=v6.at(9);
     }catch (std::out_of_range& e){
          std::cout << e.what() << std::endl;
     }
 */
class Vector{

     public:

          explicit Vector(size_t n_,size_t valor):n(n_),datos(new double[n]){};

          double at(size_t i)
          {
               if (i<0 || i>=n)
               {  
                    std::out_of_range("ta mal");
               }
               return datos[i];
          }

          const double at(size_t i)const
          {
               if (i<0 || i>=n)
               {  
                    std::out_of_range("ta mal");
               }
               return datos[i];
          }
          //Vector a{3.5,4.676,5.8899}
          Vector(std::initializer_list<double> l):n(l.size()),datos(new double[n]){
               int j=0;
               for (std::initializer_list<double>::iterator i= l.begin(); i!=l.end() ; ++i )
               {
                    datos[j]=*i;
                    j++;
               }
          }

     private:
          size_t n;
          double* datos;
};


int main()
{
     
     return 0;
}
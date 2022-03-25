#include <iostream>
using namespace std;//Avoid using std:: ....
/* Enunciado examen
    class complejo{
        public:

        private:
            double r,i;
    };
    Defina los elementos necesarios para que
    los siguientes comandos funciones
    complejo v(1.);
    complejo w();
    complejo x(2,-1.2);
    complejo y(x);

    EJERCICIO 2 
    observadores de r y de i
    operator *,+,==,!=, +
 

*/
class complejo{
        public:
            complejo(double a=0,double b=0):r(a),i(b){}
            complejo(complejo&)=default;
            double& r_get(){return r;}
            double& i_get(){return i;}
            complejo& operator+=(complejo& c){
                r+=c.r_get();
                i+=c.i_get();
                return *this;
            }
             
            bool operator ==(complejo& c){
                return r==c.r_get()&& i==c.i_get();
            }
               
        private:
            double r,i;
};
complejo& operator+(complejo& a,complejo& b){
    complejo x(a.r_get()+b.r_get(),a.i_get()+b.i_get());
    return x;
}

complejo& operator*(complejo& a,complejo& b){
    complejo x(a.r_get()*b.r_get(),a.i_get()*b.i_get());
    return x;
}

ostream& operator<<(ostream& os,complejo& c){
    os<<c.r_get()<<" "<<c.i_get();
    return os;
}

int main(){
    complejo v(1.);
    complejo w();
    complejo x(2,-1.2);
    complejo y(x);
    std::cout<<x<<" "<<y<<std::endl;
    return 0;
    
}
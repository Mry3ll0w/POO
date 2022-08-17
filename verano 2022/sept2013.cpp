#include <iostream>

using namespace std;//Avoid using std:: ....

class Complejo{
    double r,i;
public:
    
    Complejo(const double& r_ = 0.0, const double& i_=0.0):r(r_),i(i_){}
    Complejo operator = (const double& d){
        *this = Complejo(d);
        return *this;
    }

    const double& real()const{return r;}
    const double& imag()const{return i;}

    double& real(){return r;}
    double& imag(){return i;}
    
    bool operator == (Complejo& other){
        return other.i == i && other.r == r;
    }

    bool operator == (double& d){
        return i == d;
    }

    bool operator != (Complejo& other){
        return !(*this == other);
    }

    Complejo operator -(){
        return Complejo( r * -1, i * -1);
    }


};

Complejo operator + (Complejo& A, Complejo& B){
    return Complejo(A.real() + B.real(), A.imag() + B.imag()); 
}

Complejo operator - (Complejo& A , Complejo& B){
    return Complejo(A.real() - B.real(), A.imag() - B.imag());
}

Complejo operator * (Complejo& A, Complejo& B){
    return Complejo(A.real() * B.real(), A.imag() * B.imag());
}

std::ostream& operator<<(ostream &os, Complejo C)
{
    os << C.real() << "+" << C.imag()<<"i"<<endl;
    return os;
}

int main(){
    Complejo v(1.);
    Complejo w;
    Complejo X(2,-1.2);
    Complejo y(X);
    Complejo z = y;
    Complejo i2 = -1;
    X = 3.5;

return 0;
}
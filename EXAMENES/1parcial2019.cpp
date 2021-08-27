#include <iostream>
#include <vector>
class racional{
    int n,d;
    static int mcd(int,int);
public:
    racional(int a=1, int b=1 ):n(a),d(b) {}
    racional(std::initializer_list<int>& l);
    racional operator=(int);
    int n_get(){return n;}
    int d_get(){return d;}
    racional inv();
};
/* ------------------------------- OPERADORES ------------------------------- */
bool operator==(racional&a,racional&b){
    return (a.n_get()==b.n_get() && a.d_get()==b.d_get());
}
bool operator!=(racional&a,racional&b){
    return !(a==b);
}
bool operator <(racional&a,racional&b){
    return ((a.n_get()/a.d_get())<(b.n_get()/b.d_get()));
}
bool operator<=(racional&a,racional&b){
    return (a==b||a<b);
}
bool operator >=(racional&a,racional&b){
    return !(a<b);
}
bool operator >(racional&a,racional&b){
    return ((a.n_get()/a.d_get())>(b.n_get()/b.d_get()));
}
/* ------------------------------ operaciones ------------------------------ */
racional operator+(racional& a,racional& b){
    if (a.d_get()==b.d_get())
    {
        return racional(a.n_get()+b.n_get(),a.d_get());
    }
    else{
        return racional(((a.n_get()*b.d_get())+(b.n_get()*a.d_get())),(a.d_get()*b.d_get()));
    }
    
}
racional operator-(racional& a,racional& b){
    if (a.d_get()==b.d_get())
    {
        return racional(a.n_get()-b.n_get(),a.d_get());
    }
    else{
        return racional(((a.n_get()*b.d_get())-(b.n_get()*a.d_get())),(a.d_get()*b.d_get()));
    }
}
racional operator*(racional &a,racional &b){
    return racional(((a.n_get()*b.n_get())),a.d_get()*b.d_get());
}
racional operator /(racional &a,racional &b){
    return racional(a.n_get()*b.d_get(),a.d_get()*b.n_get());
}
racional racional::inv(){
    std::swap(n,d);
    return *this;
}
racional racional::operator=(int a){
    d=1;
    n=a;
    return *this;
}
std::ostream& operator<<(std::ostream&os, racional& r){
    os<<r.n_get()<<"/"<<r.d_get();
    return os;
}
/* ---------------------------- MAIN PARA PRUEBAS --------------------------- */
int main(){
    racional r={1,1};
    racional s=racional{2,3};
    if (r>s)
    {
        std::cout<<"r"<<std::endl;
    }
    
    return 0;
}
racional::racional(std::initializer_list<int>&l):n(*l.begin()),d(*l.end()){}
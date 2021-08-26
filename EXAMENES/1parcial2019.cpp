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
    racional r={0,1};
    racional s=racional{2,3};
    std::cout<<s<<std::endl;std::cout<<s<<std::endl;
    
}
racional::racional(std::initializer_list<int>&l):n(*l.begin()),d(*l.end()){}
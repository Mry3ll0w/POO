#include <vector>
#include <iostream>

using namespace std;

struct terna{
    int f, c;
    float e;

    terna(const int& fi=0, const int& co=1, float el=0):f(fi), c(co), e(el){}

    bool operator < (const terna& other) const{
        return (f < other.f) || (f == other.f && c < other.c);
    }
    bool operator == (const terna& other) const{
        return (f == other.f) && (c == other.c);
    }

    
};

std::ostream& operator<<(std::ostream& salida,const terna& t){
    salida << "["<< t.f << ", "<< t.c << "]= "<< t.e <<endl;
    return salida;
}

class MatrizDispersa{

    vector<terna> valores;
    int f, c;
public:
    MatrizDispersa(const int & filas=1, const int& cols=1);
    void asignar(const int& f, const int & c, const float& v);
    void imprime_matriz();
    
};

int main (){
    MatrizDispersa m(3,3);
    m.asignar(0,0,12.3);
    m.asignar(0,1,12.56);
    m.imprime_matriz();
    return 0;
}


MatrizDispersa::MatrizDispersa(const int & filas, const int& cols):f(filas), c(cols){}

void MatrizDispersa::asignar(const int& f, const int& c, const float& v){

    if(valores.size() == 0){
        valores.push_back(terna(f,c,v));
    }
    else {
        terna t (f,c,v);
        auto it = valores.begin();
        while (it != valores.end() && *it < t){
            it ++;
        }

        
        valores.insert(it, t);//Insertamos en orden el elemento nuevo

        for(auto i : valores)
            cout<< i<<endl;
    }

}

void MatrizDispersa::imprime_matriz(){
    bool coincide = false;
    for(int i=0; i<f; i++){
        for(int j=0; j < c; j++){
            
            for(auto it : valores){
                if (it.f == i && it.c == j){
                    cout << it.e << " ";
                    coincide = true;
                }
            }
            if(!coincide)
                cout << 0 << " ";
            
            coincide = false;
        }
        cout<<endl;
    }

}

//Falta el metodo buscar ya que lo he hecho implicitamente
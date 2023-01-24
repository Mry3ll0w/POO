#include <iostream>
#include <string>
using namespace std;//Avoid using std:: ....

class ADN{
    char * c;//Solo admite A C G T
    size_t n;
public:
    ADN(const char *input = "", const size_t& s=1){
        
        if(s < 1){
            throw invalid_argument("el tamaño de s debe ser mayor que 1");
        }
        n = s;

        //Comprobamos que los valores del input son los correctos
        string t (input);
        for(auto i : t){

            if(i != 'A' && i != 'B' && i != 'C' && i != 'G' && i != 'T'){
                throw invalid_argument("La composicion de la cadena de ADN es incorrecta");
            }

        }

        //Pasamos a reservar el espacio para la cadena si esta correcta
        c = new char[s];
        for(size_t i = 0; i < n; ++i){
            c[i] = t[i];
        }

    }

    void print(){
        for(size_t i = 0; i < n ; ++i)
            cout << c[i]<< '-';
        cout <<endl;
    }

    ADN(ADN& other){
        n = other.n;
        delete [] c;
        
        c = new char [n];
        for(size_t i = 0; i < n ; ++i)
            c[i] = other.c[i];

    }

    ADN operator = (ADN& other){
        n = other.n;
        delete[] c;

        c = new char[n];
        for (size_t i = 0; i < n; ++i)
            c[i] = other.c[i];
        
        return *this;
    }

    const size_t& size()const {return n;}
    size_t& size(){return n;}
    
    const char * cadena()const{return c;}
    char* cadena(){return c;}

};

ADN operator +(const ADN& A, const ADN& B){

    string t (A.cadena());
    string tb(B.cadena());

    t += tb;

    return ADN(t.c_str(), A.size() + B.size());
}

istream& operator >> (istream& is,ADN& A){
    string t;
    is >> t;
    ADN B(t.c_str(), t.size());
    A = B;
    return is;
}

int main(){
    ADN a("ACGTA",5), b;
    cin >> b;
    b.print();

return 0;
}
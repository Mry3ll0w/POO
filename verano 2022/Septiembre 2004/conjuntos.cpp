#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;//Avoid using std:: ....

/**
 * @brief Funcion que se encarga de determinar si dos conjuntos parametricos dados son disjuntos,
 * es decir no tienen elementos en comun.Se implementa usando la función set_intersection.
 * 
 * @param vector<T> &A, vector<T>& B
 * @return bool
 */
template <class T>
bool disjuntos(const vector<T> &A, const vector<T> &B)
{
    vector<T> resultado;
    set_intersection(A.begin(), A.end(), B.begin(), B.end(), back_inserter(resultado));
    return resultado.size() == 0; // Si es 0 son disjuntos
}

template <class T>
istream& operator >> (istream& in , vector<T>& V){
    
    cout<<"Indica cuantos elementos quieres introducir: ";
    cout<<endl;
    int n = 0;
    in >> n;
    
    for(size_t i = 0; i < n; ++i){
        T e;
        in >> e;
        V.push_back(e);
    }

    return in;
}

int main(){

    vector<int>a = {2, 3, 4, 5};
    vector<int>b={7, 8, 9, 0}; 
    cout << disjuntos(a,b) << endl;
    cin >> a;
    for(auto i : a){
        cout << i <<", ";
    }
    cout << endl;
    return 0;
}
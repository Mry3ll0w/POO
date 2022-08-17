#include <iostream>
#include <list>
#include <algorithm>
using namespace std;//Avoid using std:: ....

template <class T>
class ListaOrdenada{
    list<T> l;
public:
    
    ListaOrdenada(){}//Lista ordenada vacia de forma inicial
    
    /**
     * @brief Inserta un elemento en la lista ordenada.
     * @return none (void)
     * @param const T&e
     */
    void insertar_elemento(const T& e){
        //Asumimos que el tipo T tiene el operador < o > sobrecargado 
        l.push_back(e);
        l.sort();//Orden log n
    }

    /**
     * @brief Devuelve el iterador donde el elemento e se encuentra.
     * @return typename list<T>::iterator, if l.end() no encontrado
     * @param const T&e
     */
    typename list<T>::iterator buscar(const T& e){

        auto it = find(l.begin(),l.end(),e);

        return it;

    }
    
    typename list<T>::iterator begin() const{return l.begin();}
    
    typename list<T>::iterator end()const{return l.end();}

    
    const size_t contar(const int& e)const {
        return count_if(l.begin(),l.end(),[&](int i){return i == e;});
    }

};

int main(){
    ListaOrdenada<int>L;
    
    for (size_t i = 0; i < 10; i++)
    {
        L.insertar_elemento(i);
    }

    cout << *L.buscar(4) <<endl;
    cout << L.contar(4) <<endl;
    
return 0;
}
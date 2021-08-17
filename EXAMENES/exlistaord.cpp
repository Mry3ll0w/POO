#include <iostream>
#include <list> 
#include <algorithm>

using namespace std;//Avoid using std:: ....
size_t contar(int e,list<int>&l);
int main(){
    std::list<int>a;
    a.insert(a.end(),0);
    a.insert(a.end(),21);
    a.insert(a.end(),3);
    a.insert(a.end(),5);
    a.insert(a.end(),-1);
    //Creamos una lista con varios elementos para la funcion contar
    std::cout<<contar(3,a)<<std::endl;
    return 0;
}
size_t contar(int e,list<int>&l){
            return count_if(l.begin(),l.end(),[e](int x)->size_t{return e==x;});
            /*
            [ e ](parametros entrada)->int/float... {
                cuerpo
            }
            */
}

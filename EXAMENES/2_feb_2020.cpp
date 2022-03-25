#include <iostream>
#include <set>
#include <string>
using namespace std;//Avoid using std:: ....
class llamada;
class operador;
int main(){
    
    return 0;
}
class Instrumento{
    void virtual tocar()=0;
};
class flauta:public Instrumento{
    void tocar(){}
};
class tambor:public Instrumento{
    void tocar(){}
};

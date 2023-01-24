#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
using namespace std;//Avoid using std:: ....

/**
 * @brief Realiza la separacion de los elementos de la fecha dada para a posteriori ser tratados
 * @return none(void)
 * @param string& nombre, int& d, int& m, int& y, string source
 */
void str_splitter(string& nombre, int& d, int& m, int& y, string source){
    
    size_t i = 0;

    for(; i < source.size() && source[i] != ' '; ++i){
        nombre +=source[i];
    }

    //Obtenemos ahora el dia, mes y fecha basandonos en lo siguiente
    /**
     * La linea es igual size_nombre + espacio + fecha(10)
     */

    string dias, mes ,yyyy;
    dias += source[i+1];
    dias +=source[i+2];

    d = stoi(dias);

    mes += source[i + 4]; 
    mes += source[i + 5];

    m = stoi(mes);

    yyyy += source[i + 7];
    yyyy += source[i + 8];
    yyyy += source[i + 9];
    yyyy += source[i + 10];

    y = stoi(yyyy);


}


void cumple(const string & fname){
    //Primero abrimos el archivo y lo leemos 
    fstream fs;
    fs.open(fname);

    if(!fs.is_open()){
        cout<<"Fallo de apertura en el fichero"<<endl;
    }
    else{

        string linea;
        int d, m, y;
        string nombre;

        bool fecha_correcta=false;
        // Leemos todas las lineas hasta que haya una correcta
        while(getline(fs, linea) && !fecha_correcta){
            
            //Hacemos el split de fecha y nombre
            str_splitter(nombre,d,m,y,linea);
            
            //Creamos el tiempo
            tm t;
            t.tm_year = y;
            t.tm_mday = d;
            t.tm_mon = m;
            
            //Aqui usariamos la fecha invalida
            try{
                //Crear fecha
            }
            catch(int e){
                cout<<"Fecha incorrecta"<<endl;
                //No hace falta ya que no se pide
            }
            
            //Si la fecha es correcta ponemos a true la fecha correcta y salimos del bucle tras imprimir

            nombre = "";
            
        }
    }

}

int main(){
    
    cumple("lista.txt");


return 0;
}
// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include<map>
using namespace std;
class diccionario{
    map<string* ,string*>dict;
public:
    explicit diccionario(const string =" ");
    const size_t entradas()const{return dict.size();}
    void introduce(string& , string&);
    string traduccion(string);
    std::pair<string,string> operator [] (map<string* ,string*>);
};
int main () {
   

  return 0;
}
diccionario::diccionario(const string file_name=" "){
if (file_name !=" ")
{
    string line;
  ifstream myfile ("dict.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
        size_t i;string a,b;
        for (i = 0; line[i] != '-'; i++)
        {
            a+=line[i];
        }
        i+=1;//saltamos la barra
        for (; i < line.size(); i++)
        {
            b+=line[i];
        }
        dict.insert(make_pair(&a,&b));//vamos insertando las parejas
    }
    myfile.close();
  }else throw runtime_error("Error de apertura de fichero");

}  
}

void diccionario::introduce(string& p_ing, string& p_esp){
    if (p_ing==" " or p_esp==" ")
    {
        throw runtime_error("Las palabras introducidas para la traducir es incorrecta");
    }
    dict.insert(make_pair(&p_ing, &p_esp));
    
}

string diccionario::traduccion(string p_ing){
    if (dict.find(&p_ing)!=dict.end())
    {
       return *dict[&p_ing];
    }
    else{
        return string(" ");
    }
    
}

std::pair<string,string>diccionario::operator [] (map<string* ,string*>m){
    
}
#ifndef BINARIO_HPP
#define BINARIO_HPP
#include <iostream>

class binario{
    private:    
        static const size_t bits_elto = 8 *sizeof(unsigned char);//CHAR_BIt= 8 (8 bits por byte)
        size_t n;/* longitud en bits */
        size_t m;/* Longitud del vector de enteros */
        unsigned* bits; //Vector de enteros

    public:
        binario(unsigned n_=1):n(n_),m((n+(n*8)-1)/(n*8)),bits(new unsigned[n]){//Ya que minimo tendra un bit n=1 default
            //RESERVA dinamica de bits
            /* Rellenamos los elementos de bits vacios */
            for (size_t i = 0; i < n; i++)
            {
                bits[i] = 0;//Rellenamos los n bits a 0
            }
        }
        binario(binario&& b):bits(b.bits),n(b.n),m(b.m){
            b.bits=nullptr; // Apuntamos a nada para que el destructor lo elimine a posteriori
            b.n=1;/* Reseteamos el size minimo de los bits (opcional) */
        }
        ~binario(){
            delete[] bits; //ya que el compilador no es capaz de eliminar el espacio allocated
        }
        /* Borrar tras comprobar */
        void show_bits(){
            for (size_t i = 0; i < n; i++)
            {
                std::cout<<bits[i]<<" ";
            }
            std::cout<<std::endl;/* Salto de linea extra */
        }
        binario& operator=(const binario& a){
            n=a.n; m=a.m; 
            delete [] bits;
            bits = new unsigned[a.n];//Eliminamos la reserva de memoria y la reservamos con el new size
            for (size_t i = 0; i < n; i++)
            {
                bits[i]= a.bits[i]; //Copiamos los bits de a en *this
            }
            return *this;
        }
};


#endif

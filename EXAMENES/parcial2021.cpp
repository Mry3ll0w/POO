#include <iostream>
#include <vector>
class MatrizDispersa{
        struct terna{
                size_t f,c;
                double v;
        };
        std::vector<terna>m;
        size_t f;
        size_t c;
        bool buscar(size_t f, size_t c, size_t& pos);
public:
        MatrizDispersa(size_t m_=1, size_t n_=1);
        void asignar(size_t m, size_t n, double v);
        void valor(size_t m,size_t n);
        size_t filas(){return m;}
        size_t columnas(){return n;}
        size_t n_valores(){return m.size();}
};

int main(){
        return 0;
}

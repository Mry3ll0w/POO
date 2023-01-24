#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std; // Avoid using std:: ....

/**
 * Ejercicio 1 : Clase Binario
 */

class Binario
{
    static const size_t bits_elto = CHAR_BIT * sizeof(unsigned);
    size_t n, m;
    unsigned *bits;

public:
    // para imprimir por pantalla, no es necesario
    const size_t getn() { return n; }

    Binario(const size_t size = 1) : n(size), m((n - bits_elto - 1) / bits_elto), bits(new unsigned[n])
    {
        for (size_t i = 0; i < n; ++i)
        {
            bits[n] = 0;
        }
    }

    unsigned &operator[](const int &i)
    {
        if (i < 0 || i >= n)
            throw std::invalid_argument("overflow");
        return bits[i];
    }

    Binario(Binario &&b) : n(b.n), m(b.m), bits(b.bits)
    {
        b.bits = nullptr;
        b.n = 0;
        b.m = 0;
    }

    Binario(const Binario &b)
    {
        // delete[] bits;
        n = b.n;
        m = b.m;
        bits = new unsigned[n];
        for (size_t i = 0; i < n; ++i)
        {
            bits[i] = b.bits[i];
        }
    }

    Binario operator=(Binario b)
    {
        delete[] bits;
        n = b.n;
        m = b.m;
        bits = new unsigned[n];
        for (size_t i = 0; i < n; ++i)
        {
            bits[i] = b.bits[i];
        }
        return *this;
    }

    Binario operator~()
    {
        Binario b(n);

        for (size_t i = 0; i < n; ++i)
        {
            b[i] = 1;
        }
        return b;
    }

    ~Binario()
    {
        delete[] bits;
    }
};

// No es parte del ejericicio es para comprobar
ostream &operator<<(ostream &os, Binario &b)
{
    for (size_t i = 0; i < b.getn(); ++i)
    {
        os << b[i];
    }
    return os;
}

// Ejercicio 2
class Llamada;
class Operador;
typedef struct DatosLlamada
{
};
class Llamada
{
    map<Operador *, DatosLlamada *> OD;

public:
    void asocia(Operador *o, DatosLlamada *d)
    {
        if (OD.find(o) != OD.end())
        {
            OD[o] = d;
        }
        else
        {
            OD.insert(make_pair(o, d));
        }
    }
    DatosLlamada *asociado(Operador *o)
    {
        if (OD.find(o) == OD.end())
        {
            return nullptr;
        }
        else
        {
            return OD[o];
        }
    }
};

class Operador
{
    map<Llamada *, DatosLlamada *> LD;

public:
    void asocia(Llamada *l, DatosLlamada *d)
    {
        if (LD.find(l) != LD.end())
        {
            LD[l] = d;
        }
        else
        {
            LD.insert(make_pair(l, d));
        }
    }
    DatosLlamada *asociado(Llamada *l)
    {
        if (LD.find(l) == LD.end())
        {
            return nullptr;
        }
        else
        {
            return LD[l];
        }
    }
};

int main()
{
}

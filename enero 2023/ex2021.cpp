#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; // Avoid using std:: ....

struct Terna
{
    int iFila, iCol;
    double dValor;
    Terna(int f = 0, int c = 0, double d = 0) : iFila(f), iCol(c), dValor(d) {}
    bool operator<(const Terna &t)
    {
        return (iFila < t.iFila) ||
               (iFila == t.iFila && iCol < t.iCol);
    }
    bool operator==(const Terna &t) // Para que la busqueda sea mas sencilla
    {
        return (iFila == t.iFila && iCol == t.iCol);
    }
};

class MatrizDispersa
{
    vector<Terna> aValores;
    size_t iM_, iN_;

    bool buscar(const int &f, const int &c, int &iIndice);

public:
    explicit MatrizDispersa(const int &f = 1, const int &c = 1);
    void asignarValor(const int &f, const int &c, const double &valor);
    double &valor(const int &f, const int &c);
    vector<Terna> &valores() { return aValores; }
    const int filas() const { return iM_; }
    const int columnas() const { return iN_; }
    size_t &filas() { return iM_; }
    size_t &columnas() { return iN_; }
    const int nValores() { return aValores.size(); }
    MatrizDispersa(std::initializer_list<Terna> lTernas, int &m, int n) : iM_(m), iN_(n)
    {
        for (auto i : lTernas)
        {
            if (i.dValor != 0)
                asignarValor(i.iFila, i.iCol, i.dValor);
        }
    }

    void mostrarMatriz()
    {
        // No lo pide pero para pruebas va fresco
        for (auto i : aValores)
        {
            cout << "Fila " << i.iFila << ", "
                 << "Columna " << i.iCol << ": " << i.dValor << endl;
        }
    }
};

// Funcion Swap Eficiente
void swapMatrices(MatrizDispersa &A, MatrizDispersa &B)
{
    std::swap(A.filas(), B.filas());
    std::swap(A.columnas(), B.columnas());
    std::swap(A.valores(), B.valores());
}

int main()
{
    MatrizDispersa M(3, 3), M2;
    M.asignarValor(0, 2, 4);
    M.asignarValor(1, 2, 1);
    M.asignarValor(0, 1, 3);
    M.asignarValor(1, 2, 45);
    swapMatrices(M, M2);
    M.valor(0, 0) = 55;
    M2.mostrarMatriz();

    return 0;
}

// Apartado 2: Implementacion de los metodos de matriz dispersa

bool MatrizDispersa::buscar(const int &f, const int &c, int &iIndice)
{
    iIndice = 0;
    for (; iIndice < aValores.size() && !(Terna(f, c) == aValores[iIndice]); ++iIndice)
    {
    }

    if (iIndice == aValores.size())
        return false;
    else
        return aValores[iIndice].dValor != 0; // si no es 0 existe una terna con valor
}

MatrizDispersa::MatrizDispersa(const int &f, const int &c) : iN_(f), iM_(c)
{
    if (f < 1 || c < 1)
        throw std::invalid_argument("Medidas de la matriz incorrectas");
}

void MatrizDispersa::asignarValor(const int &f, const int &c, const double &d)
{
    if (f < 0 && c < 0 || f >= iM_ || c >= iN_)
        throw std::invalid_argument("Indices de la matriz incorrectos");

    int iIndice = 0;
    if (buscar(f, c, iIndice))
    { // Si hay elemento simplemente reasignamos el valor
        aValores[iIndice].dValor = d;
    }
    else
    {
        aValores.insert(aValores.begin(), Terna(f, c, d));
        std::sort(aValores.begin(), aValores.end());
    }
}

double &MatrizDispersa::valor(const int &f, const int &c)
{
    try
    {
        if (f < 0 && c < 0 || f >= iM_ || c >= iN_)
            throw std::out_of_range("Indices de la matriz incorrectos");
    }
    catch (std::exception &e)
    {
        cerr << e.what() << endl;
    }

    int i;
    if (buscar(f, c, i))
    {
        return aValores[i].dValor;
    }
    else
        throw std::invalid_argument("No existe valor");
}
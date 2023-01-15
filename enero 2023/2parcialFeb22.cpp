#include <iostream>
#include <map>
#include <set>
using namespace std; // Avoid using std:: ....

int main()
{

    return 0;
}

/**
 * Ejercicio 1a : Clase asociacion entre vehiculo y cliente
 * Tiene un atributo de enlace Reserva
 */

typedef struct Vehiculo
{
    // ...
};
typedef struct Cliente
{
    // ...
};
typedef struct Reserva
{
    // ...
};

class ACV
{
    map<Cliente *, map<Reserva *, Vehiculo *>> CV;
    map<Vehiculo *, pair<Reserva *, Cliente *>> VC;

public:
    void asocia(Cliente *c, Reserva *r, Vehiculo *v)
    {
        // asociacion directa
        if (CV.find(c) != CV.end())
        {
            CV.erase(CV.find(c));
            map<Reserva *, Vehiculo *> rv;
            rv.insert(make_pair(r, v));
            CV.insert(make_pair(c, rv));
        }
        else
        {
            map<Reserva *, Vehiculo *> rv;
            rv.insert(make_pair(r, v));
            CV.insert(make_pair(c, rv));
        }

        // asociacion indirecta
        if (VC.find(v) != VC.end())
        {
            VC.erase(VC.find(v));
            VC.insert(make_pair(v, make_pair(r, c)));
        }
        else
        {
            VC.insert(make_pair(v, make_pair(r, c)));
        }
    }

    void asocia(Vehiculo *v, Reserva *r, Cliente *c)
    {
        asocia(v, r, c);
    }

    map<Reserva *, Vehiculo *> asociados(Cliente *c)
    {
        if (CV.find(c) != CV.end())
            return CV[c];
        else
            return map<Reserva *, Vehiculo *>();
    }

    pair<Reserva *, Cliente *> asociados(Vehiculo *v)
    {
        if (VC.find(v) != VC.end())
            return VC[v];
        else
            return pair<Reserva *, Cliente *>();
    }
};

/**
 * Ejercicio 1b: Crear asociacion entre cliente-contrato y vehiculo-contrato
 */
class Detalle;
class Contrato;
class Vehiculo2
{
    pair<Detalle *, Contrato *> DC;

public:
    // Pereza implementar
};
class Contrato
{
    Cliente2 *c_;
    pair<Detalle *, Vehiculo2 *> DV;

public:
    void asociaCliente(Cliente2 *c)
    {
        c_ = c;
    }
    Cliente2 *asociado() { return c_; }
    void asociaVehiculo(Detalle *d, Vehiculo2 *v)
    {
        DV = make_pair(d, v);
    }
    pair<Detalle *, Vehiculo2 *> vehiculosAsociados() { return DV; }
};

class Cliente2
{
    set<Contrato *> setContratos_;

public:
    void asociaContrato(Contrato *c)
    {
        setContratos_.insert(c);
    }

    set<Contrato *> asociados() { return setContratos_; }
};

// Ejercicio 2 : Matriz Dispersa

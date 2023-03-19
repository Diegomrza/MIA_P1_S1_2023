#ifndef CL_H
#define CL_H

#include "../DefinicionStructs/structParticion.h"
#include "../DefinicionStructs/structEBR.h"

//Cl de calculate
class Cl
{
private:
    /* data */
public:
    Cl(EBR);
    ~Cl();

    EBR dato;
    Cl *siguiente;

};

Cl::Cl(EBR dato) {
    this->dato = dato;
    this->siguiente = NULL;
}

Cl::~Cl()
{
}

#endif
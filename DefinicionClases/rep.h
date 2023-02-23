#ifndef REP_H
#define REP_H

#include <string>
#include "../DefinicionStructs/structMBR.h"
#include <fstream>
#include <iostream>
#include <chrono>

class rep
{
private:
    /* data */
public:
    rep(std::string);
    ~rep();

    void mostrar(std::string);
};

rep::rep(std::string ruta)
{
    this->mostrar(ruta);
}

rep::~rep()
{
}

#endif
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
    void analizador_rep(std::string);
    
public:
    rep(std::string);
    ~rep();


    void mostrar(std::string);
};

rep::rep(std::string ruta)
{
    this->analizador_rep(ruta);
}

rep::~rep()
{
}

#endif
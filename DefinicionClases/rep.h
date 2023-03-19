#ifndef REP_H
#define REP_H

#include <string>
#include "../DefinicionStructs/structMBR.h"
#include "../Grafos/grafo.h"
#include <fstream>
#include <iostream>
#include <chrono>

class rep
{
private:

    std::string name;
    std::string path;
    std::string id;
    std::string ruta;

    void analizador_rep(std::string);
    void administrador_rep(std::string);

    bool verificar_name(std::string);
    bool verificar_path(std::string);
    bool verificar_id(std::string);
    bool verificar_ruta(std::string);

    std::string split_text_rep(std::string, char, int);
    std::string toLower_rep(std::string);
    std::string toUpper_rep(std::string);
    
public:
    rep(std::string);
    ~rep();

    void mostrar(std::string);
};

rep::rep(std::string texto)
{
    this->name = "";
    this->path = "";
    this->id = "";
    this->ruta = "";

    this->analizador_rep(texto);
}

rep::~rep()
{
}

#endif
#ifndef MKDISK_H
#define MKDISK_H

#include <string>
#include <fstream>
#include <iostream>
#include "../DefinicionStructs/structMBR.h"
#include "chrono"

class mkdisk
{
private:
    void crear_disco(std::string);
    int numero_random();
    void escribir_mbr(std::string, MBR);
    void analizador_mkdisk(std::string);

    int tamanio;
    std::string unidades;
    std::string ruta;

public:
    mkdisk(std::string);
    ~mkdisk();
};

mkdisk::mkdisk(std::string texto)
{
    this->analizador_mkdisk(texto);
}

mkdisk::~mkdisk()
{
}

#endif
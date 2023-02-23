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
    std::string split_text_mkdisk(std::string, char, int);

    int tamanio;            //Obligatorio
    std::string unidades = "M";   //Opcional => K o M
    std::string ruta;       //Obligatorio

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
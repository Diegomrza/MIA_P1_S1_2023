#ifndef MKDISK_H
#define MKDISK_H

#include <string>
#include <fstream>
#include <iostream>
#include "../DefinicionStructs/structMBR.h"
#include "chrono"
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h> //Para crear carpetas con mkdir

class mkdisk
{
private:
    void crear_disco(std::string, int, std::string); //Parámetros => ruta, tamaño, unidad
    int numero_random();
    void escribir_mbr(std::string, MBR);
    void analizador_mkdisk(std::string);
    std::string split_text_mkdisk(std::string, char, int);

    bool verify_tamanio_mkdisk(std::string);
    bool verify_unidades_mkdisk(std::string);
    bool verify_ruta_mkdisk(std::string);

    std::string errores_mkdisk(int);
    void mensaje_error_crear_disco();

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
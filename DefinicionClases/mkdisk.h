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
    //Funcion principal
    void analizador_mkdisk(std::string);

    //Funciones de verificacion de parametros
    bool verify_tamanio_mkdisk(std::string);
    bool verify_unidades_mkdisk(std::string);
    bool verify_ruta_mkdisk(std::string);
    bool verify_fit_mkdisk(std::string);

    //Funciones de ayuda
    std::string split_text_mkdisk(std::string, char, int);
    int numero_random();
    void escribir_mbr(std::string, MBR);
    void crear_disco(std::string, int, std::string); // Parámetros => ruta, tamaño, unidad

    std::string errores_mkdisk(int);  //  Devuelve el mensaje de error correspondiente
    void mensaje_error_crear_disco(); //  Mensaje de error al crear el disco

    //Parametros
    std::string fit;
    int tamanio;
    std::string unidades;
    std::string ruta;

public:
    mkdisk(std::string);
    ~mkdisk();
};

mkdisk::mkdisk(std::string texto)
{
    this->tamanio = 0;    // size => Obligatorio
    this->unidades = "M"; // unit => Opcional => K o M
    this->ruta = "";      // path => Obligatorio
    this->fit = "FF";     // fit => Opcional => FF, BF, WF
    this->analizador_mkdisk(texto);
}

mkdisk::~mkdisk()
{
}

#endif
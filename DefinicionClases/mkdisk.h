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
#include <dirent.h> //Para abrir un directorio con opendir
#include <errno.h> //Para obtener el error de mkdir
#include <vector> //Para el vector de numeros aleatorios
#include <algorithm> //Para el find del vector de numeros aleatorios
#include "../DefinicionStructs/structNumerosAleatorios.h"

class mkdisk
{
private:
    //Funcion principal
    void analizador_mkdisk(std::string);

    //Funciones de verificacion de parametros
    bool verificar_tamanio_mkdisk(std::string);
    bool verificar_unidades_mkdisk(std::string);
    bool verificar_ruta_mkdisk(std::string);
    bool verificar_fit_mkdisk(std::string);

    //Funciones de ayuda
    std::string split_text_mkdisk(std::string, char, int);
    int numero_random();
    void escribir_mbr(std::string, MBR);
    void mostrar_mbr(MBR);
    void crear_disco(std::string, int, std::string); // Parámetros => ruta, tamaño, unidad
    std::string tolower_mkdisk(std::string);

    std::string errores_mkdisk(int);  //  Devuelve el mensaje de error correspondiente

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
#ifndef MKDISK_H
#define MKDISK_H

#include <string>
#include <fstream>  //Para leer y escribir en un archivo
#include <iostream> //Para entrada y salida de datos

#include "chrono"   // Para obtener la fecha y hora c++ 11
#include <time.h>   // Para obtener la fecha y hora c y c++
#include <stdlib.h> // para la generacion de numeros aleatorios
#include <sys/stat.h> //Para crear carpetas con mkdir
#include <dirent.h> //Para abrir un directorio con opendir
#include <errno.h> //Para obtener el error de mkdir
#include "../DefinicionStructs/structMBR.h"
#include "../DefinicionClases/comentario.h"

class mkdisk {
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
    std::string tolower_mkdisk(std::string);
    int numero_random();
    
    void crear_disco(std::string, int, std::string); // Parámetros => ruta, tamaño, unidad
    void crear_carpeta(std::string);
    void escribir_mbr(std::string, MBR);
    void mostrar_mbr(MBR);

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

mkdisk::mkdisk(std::string texto) {
    this->tamanio = 0;    // size => Obligatorio
    this->unidades = "M"; // unit => Opcional => K o M
    this->ruta = "";      // path => Obligatorio
    this->fit = "FF";     // fit => Opcional => FF, BF, WF
    this->analizador_mkdisk(texto);
}

mkdisk::~mkdisk() {
}

#endif
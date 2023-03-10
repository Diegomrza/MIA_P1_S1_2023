#ifndef RMDISK_H
#define RMDISK_H

#include <string>
#include <iostream>
#include "./comentario.h"

class rmdisk
{
private:
    std::string ruta;
    void analizador_rmdisk(std::string);
    std::string split_text_rmdisk(std::string, char, int);
    std::string toLower_rmdisk(std::string);
    bool verificar_ruta_rmdisk(std::string);
    bool eliminar_disco(std::string);
    
public:
    rmdisk(std::string);
    ~rmdisk();
};

rmdisk::rmdisk(std::string ruta)
{
    this->ruta = ruta;
    this->analizador_rmdisk(this->ruta);
}

rmdisk::~rmdisk()
{
}


#endif
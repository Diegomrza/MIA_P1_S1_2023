#ifndef RMDISK_H
#define RMDISK_H

#include <string>
#include <iostream>

class rmdisk
{
private:
    std::string ruta;
    void analizador_rmdisk(std::string);
    std::string split_text_rmdisk(std::string, char, int);
    bool verify_ruta_rmdisk(std::string);
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
#ifndef FDISK_H
#define FDISK_H

#include <string>

class fdisk
{
private:
    /* data */
    int tamanio;
    std::string unidades;
    std::string ruta;
    std::string nombre;

public:
    fdisk(/* args */);
    ~fdisk();
};

fdisk::fdisk(/* args */)
{
}

fdisk::~fdisk()
{
}


#endif
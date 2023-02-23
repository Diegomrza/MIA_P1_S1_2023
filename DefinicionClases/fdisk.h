#ifndef FDISK_H
#define FDISK_H

#include <string>

class fdisk
{
private:
    int tamanio;
    std::string unidades;
    std::string ruta;
    std::string nombre;

    void analizador_fdisk(std::string);

public:
    fdisk(std::string);
    ~fdisk();
};

fdisk::fdisk(std::string texto)
{
    this->analizador_fdisk(texto);
}

fdisk::~fdisk()
{
}

#endif
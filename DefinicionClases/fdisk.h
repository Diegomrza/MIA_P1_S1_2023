#ifndef FDISK_H
#define FDISK_H

#include <string>
#include <regex>
#include "../DefinicionStructs/structParticion.h"

class fdisk
{
private:
    int tamanio;          // Obligatorio
    std::string ruta;     // Obligatorio
    std::string nombre;   // Obligatorio

    std::string tipo = "P";     // Opcional
    std::string ajuste = "WF";   // Opcional
    std::string eliminar; // Opcional
    std::string unidades = "K"; // Opcional

    void analizador_fdisk(std::string);
    std::string split_text_fdisk(std::string, char, int);
    void crear_particion();

    bool verify_tamanio(std::string);
    bool verify_ruta(std::string);
    bool verify_nombre(std::string);

    bool verify_tipo(std::string);
    bool verify_ajuste(std::string);
    bool verify_eliminar(std::string);
    bool verify_unidades(std::string);

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
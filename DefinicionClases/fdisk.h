#ifndef FDISK_H
#define FDISK_H

#include <string>
#include <regex>
#include "../DefinicionStructs/structParticion.h"

class fdisk
{
private:
    int tamanio;          // Obligatorio al crear
    std::string ruta;     // Obligatorio
    std::string nombre;   // Obligatorio

    std::string unidades; // Opcional
    std::string tipo;     // Opcional
    std::string ajuste;   // Opcional
    std::string eliminar; // Opcional
    std::string agregar; //Opcional
    

    void analizador_fdisk(std::string);
    std::string split_text_fdisk(std::string, char, int);
    std::string toLower_fdisk(std::string);
    void crear_particion();

    bool verificar_tamanio(std::string);
    bool verificar_ruta(std::string);
    bool verificar_nombre(std::string);

    bool verificar_tipo(std::string);
    bool verificar_ajuste(std::string);
    bool verificar_eliminar(std::string);
    bool verificar_unidades(std::string);
    bool verificar_agregar(std::string);

public:
    fdisk(std::string);
    ~fdisk();
};

fdisk::fdisk(std::string texto)
{
    this->tamanio = 0;
    this->ruta = "";
    this->nombre = "";

    this->unidades = "K";
    this->tipo = "P";
    this->ajuste = "WF";
    this->eliminar = "";
    this->agregar = "";
    this->analizador_fdisk(texto);
}

fdisk::~fdisk()
{
}

#endif
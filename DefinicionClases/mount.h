#ifndef MOUNT_H
#define MOUNT_H

#include <iostream>
#include <string>
#include <regex>
#include "./comentario.h"

class mount
{
private:
    std::string ruta;   //Ruta del disco existente
    std::string nombre; //Nombre de la partición a montar
    void analizador_mount(std::string texto);
    bool verificar_ruta(std::string texto);
    bool verificar_nombre(std::string texto);
    void montar_particion();

    std::string toLower_mount(std::string texto);
    std::string split_text_mount(std::string texto, char delimitador, int posicion);

public:
    mount(std::string);
    ~mount();
};

mount::mount(std::string texto)
{
    this->ruta = "";
    this->nombre = "";
    this->analizador_mount(texto);
}

mount::~mount()
{
}

#endif
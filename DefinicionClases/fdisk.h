#ifndef FDISK_H
#define FDISK_H

#include <string>
#include <regex>
#include "../DefinicionStructs/structParticion.h"
#include "../DefinicionStructs/structMBR.h"
#include "../DefinicionStructs/structEBR.h"
#include "../DefinicionClases/comentario.h"

class fdisk
{
private:
    int tamanio;        // Obligatorio al crear
    std::string ruta;   // Obligatorio
    std::string nombre; // Obligatorio

    std::string unidades; // Opcional
    std::string tipo;     // Opcional
    std::string ajuste;   // Opcional
    std::string eliminar; // Opcional
    int agregar;  // Opcional

    
    std::string split_text_fdisk(std::string, char, int);
    std::string toLower_fdisk(std::string);
    int contador_particiones_primarias(MBR);
    bool existe_particion_extendida(MBR);

    void administrador_fdisk();

    void crear_particion();
    void crear_particion_primaria(MBR);
    void crear_particion_extendida(MBR);
    void crear_particion_logica(MBR);

    void eliminar_particion();
    void modificar_particion(structParticion &);
    void ordenar_particiones();

    void escribir_ebr(EBR);
    void reescribir_mbr(MBR);
    void mostrar_mbr();
    void mostrar_particion(structParticion);

    // Función inicial
    void analizador_fdisk(std::string);

    //Parámetros obligatorios
    bool verificar_tamanio(std::string);
    bool verificar_ruta(std::string);
    bool verificar_nombre(std::string);

    //Parámetros opcionales
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
    this->agregar = 0;
    this->analizador_fdisk(texto);
}

fdisk::~fdisk()
{
}

#endif
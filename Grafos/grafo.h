#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <graphviz/gvc.h>   //libreria para generar grafos
#include <graphviz/cgraph.h> //libreria para generar grafos
#include "../DefinicionStructs/structMBR.h"
#include "../DefinicionStructs/structEBR.h"
#include <fstream>
#include <iostream>

class Grafo
{
private:
    void administrador_grafos(std::string, std::string, std::string, std::string); //Tipo, ruta del disco, formato, nombre del archivo

    std::string generar_codigo_graphviz(MBR);  //devuelve un string con el codigo del grafo
    std::string generar_archivo_dot(std::string, std::string, std::string);      //devuelve la ruta del archivo dot que creó

    void generar_grafo(std::string, std::string, MBR);
    void generar(std::string, std::string, MBR);
    MBR obtener_mbr(std::string);

    std::string reporte_mbr(std::string, std::string, std::string);
    std::string reporte_disk(std::string, std::string, std::string);
    std::string reporte_inode(std::string, std::string, std::string);
    std::string reporte_journaling(std::string, std::string, std::string);
    std::string reporte_block(std::string, std::string, std::string);
    std::string reporte_bm_inode(std::string, std::string, std::string);
    std::string reporte_bm_block(std::string, std::string, std::string);
    std::string reporte_tree(std::string, std::string, std::string);
    std::string reporte_sb(std::string, std::string, std::string);
    std::string reporte_file(std::string, std::string, std::string);
    std::string reporte_ls(std::string, std::string, std::string);

public:
    Grafo(std::string, std::string, std::string, std::string);
    ~Grafo();
};

Grafo::Grafo(std::string tipo, std::string ruta, std::string formato, std::string nombre)
{
    this->administrador_grafos(tipo, ruta, formato, nombre);
    //this->generar_grafo(ruta, formato, mbr);
    //this->generar(ruta, formato, mbr);
}

Grafo::~Grafo()
{
}

#endif
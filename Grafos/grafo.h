#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <fstream>
#include <iostream>

class grafo
{
private:
    /* data */
public:
    grafo(/* args */);
    ~grafo();

    std::string generar_codigo_graphviz();  //devuelve un string con el codigo del grafo
    std::string generar_archivo_dot(std::string, std::string, std::string);      //devuelve la ruta del archivo dot que creó
    void generar_grafo(std::string, std::string);
};

grafo::grafo(/* args */)
{
}

grafo::~grafo()
{
}

#endif
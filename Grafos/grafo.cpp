#include "grafo.h"

std::string grafo::generar_archivo_dot(std::string nombre_archivo, std::string ruta, std::string codigo_graphviz)
{
    std::string filename(ruta + nombre_archivo + ".dot");
    std::fstream file_out;

    file_out.open(filename, std::ios_base::out);
    if (!file_out.is_open())
    {
        return "Error";
    }
    file_out << codigo_graphviz << std::endl;
    //std::cout << "La escritura fue un exito" << std::endl;
    
    return filename;
}

std::string grafo::generar_codigo_graphviz()
{
    std::string grafo = "digraph MyGraph {";
    grafo += "Node1 -> Node2;";
    grafo += "}";
    return grafo;
}

void grafo::generar_grafo(std::string ruta, std::string formato) {
    if (this->generar_archivo_dot("grafo1", "", this->generar_codigo_graphviz()).compare("Error")) {
        std::cout << "Error al abrir el archivo: " << ruta << '\n';
        return;
    }
    std::string cmd = "dot -T"+formato + " " + ruta + " -o " + ruta + "." + formato;
    system(cmd.c_str());
}
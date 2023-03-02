#include "../DefinicionClases/rmdisk.h"

void rmdisk::analizador_rmdisk(std::string comando)
{
    std::cout << "Comando: " << comando << std::endl;
    bool bandera = false;
    (std::regex_search(comando, std::regex(">path")) == true) ? bandera = this->verify_ruta_rmdisk(comando) : bandera = false;
    if (bandera) {
        this->eliminar_disco(this->ruta);
    }
}

bool rmdisk::verify_ruta_rmdisk(std::string texto)
{
    std::smatch ru;
    if (std::regex_search(texto, ru, std::regex(">path=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")")) == true) {
        this->ruta = this->split_text_rmdisk(ru.str(), '=', 2);
        return true;
    }
    std::cout << "Error: Ruta no valida" << std::endl;
    return false;
}

bool rmdisk::eliminar_disco(std::string ruta)
{
    if (std::remove(ruta.c_str()) == 0) {
        std::cout << "Disco eliminado" << std::endl;
        return true;
    }
    std::cout << "Error: No se pudo eliminar el disco" << std::endl;
    return false;
}

std::string rmdisk::split_text_rmdisk(std::string texto, char delimitador, int posicion){
    std::string aux;
    std::stringstream input_stringstream(texto);
    for (int i = 0; i < posicion; i++)
    {
        getline(input_stringstream, aux, delimitador);
    }
    return aux;
}
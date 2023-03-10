#include "../DefinicionClases/rmdisk.h"

void rmdisk::analizador_rmdisk(std::string comando) {
    bool bandera = false;
    std::string aux = this->toLower_rmdisk(comando);

    if (std::regex_search(comando, std::regex("#.*"))) comentario co(comando);

    (std::regex_search(aux, std::regex(">path")) == true) ? bandera = this->verificar_ruta_rmdisk(comando) : bandera = false;
    if (bandera) {
        this->eliminar_disco(this->ruta);
    }
}

bool rmdisk::verificar_ruta_rmdisk(std::string texto) {
    std::smatch ru;

    if (std::regex_search(texto, ru, std::regex("=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")")) == true) {
        this->ruta = this->split_text_rmdisk(regex_replace(ru.str(), std::regex("\""), ""), '=', 2);
        return true;
    }
    std::cout << "Error: Ruta no valida" << std::endl;
    return false;
}

bool rmdisk::eliminar_disco(std::string ruta) {
    std::cout<<"Está seguro de que desea eliminar el disco "<< this->ruta<<"? (y/n)\n>> ";
    std::string opcion;
    getline(std::cin, opcion);
    opcion = this->toLower_rmdisk(opcion);
    if(opcion == "y") {
        if (std::remove(ruta.c_str()) == 0){
            std::cout << "Disco eliminado" << std::endl;
            return true;
        }
        std::cout << "Error: No se pudo eliminar el disco porque no existe." << std::endl;
    } else {
        std::cout << "Operación cancelada." << std::endl;
    }
    return false;
}

std::string rmdisk::split_text_rmdisk(std::string texto, char delimitador, int posicion) {
    std::string aux;
    std::stringstream input_stringstream(texto);
    for (int i = 0; i < posicion; i++) {
        getline(input_stringstream, aux, delimitador);
    }
    return aux;
}

std::string rmdisk::toLower_rmdisk(std::string texto) {
    std::string aux;
    for (int i = 0; i < texto.length(); i++) {
        aux += tolower(texto[i]);
    }
    return aux;
}
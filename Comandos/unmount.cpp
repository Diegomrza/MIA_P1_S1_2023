#include "../DefinicionClases/unmount.h"

void unmount::analizador_unmount(std::string texto) {
    /**
     * >(I|i)(D|d)=([a-zA-Z0-9_]+)
     */
    bool bandera = true;

    (std::regex_search(texto, std::regex(">(I|i)(D|d)"))) ? bandera = this->verificar_id(texto) : bandera = false;
    
    //Lee el posible comentario en unmount
    if (std::regex_search(texto, std::regex("#.*"))) comentario co(texto);

    if (!bandera) {
        std::cout << "Error: el comando no es valido." << std::endl;
        return;
    }
    this->desmontar_particion();
}

bool unmount::verificar_id(std::string texto) {
    /**
     * >(I|i)(D|d)=([a-zA-Z0-9_]+)
     */
    if (std::regex_search(texto, std::regex(">(I|i)(D|d)=([a-zA-Z0-9_]+)"))) {
        this->id = this->split_text_unmount(texto, '=', 2);
        return true;
    } else {
        return false;
        std::cout << "Error: el id no es valido." << std::endl;
    }
}

void unmount::desmontar_particion() {
    std::cout << "Desmount completo" << std::endl;
}

std::string unmount::toLower_unmount(std::string texto) {
    std::string aux = "";
    for (int i = 0; i < texto.length(); i++) {
        aux += tolower(texto[i]);
    }
    return aux;
}

std::string unmount::split_text_unmount(std::string texto, char delimitador, int posicion) {
    std::string aux;
    std::stringstream input_stringstream(texto);
    for (int i = 0; i < posicion; i++)
    {
        getline(input_stringstream, aux, delimitador);
    }
    return aux;
}
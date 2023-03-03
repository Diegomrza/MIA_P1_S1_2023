#include "../DefinicionClases/unmount.h"

void unmount::analizador_unmount(std::string texto)
{
    bool bandera = true;

    /**
     * (U|u)(N|n)(M|m)(O|o)(U|u)(N|n)(T|t)     
    */
    if (std::regex_search(texto, std::regex(">(U|u)(N|n)(M|m)(O|o)(U|u)(N|n)(T|t)"))) {
        /**
         * >(I|i)(D|d)=([a-zA-Z0-9_]+)
        */
        if (std::regex_search(texto, std::regex(">(I|i)(D|d)=([a-zA-Z0-9_]+)"))) {
            this->id = this->split_text_unmount(texto, '=', 2);
        } else {
            bandera = false;
            std::cout << "Error: el id no es valido" << std::endl;
        }
    } else {
        std::cout << "Error de comando unmount" << std::endl;
        bandera = false;
    }

    if (bandera) {
        this->desmontar();
    }
}

void unmount::desmontar()
{
    
}

std::string unmount::toLower_unmount(std::string texto)
{
    std::string aux = "";
    for (int i = 0; i < texto.length(); i++)
    {
        aux += tolower(texto[i]);
    }
    return aux;
}

std::string unmount::split_text_unmount(std::string texto, char delimitador, int posicion)
{
    std::string aux;
    std::stringstream input_stringstream(texto);
    for (int i = 0; i < posicion; i++)
    {
        getline(input_stringstream, aux, delimitador);
    }
    return aux;
}
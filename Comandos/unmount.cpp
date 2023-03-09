#include "../DefinicionClases/unmount.h"

void unmount::analizador_unmount(std::string texto)
{
    /**
     * (U|u)(N|n)(M|m)(O|o)(U|u)(N|n)(T|t)
     */
    if (std::regex_search(texto, std::regex(">(U|u)(N|n)(M|m)(O|o)(U|u)(N|n)(T|t)")) == false)
    {
        std::cout << "Error de comando unmount" << std::endl;
        return;
    }
    if (verificar_id(texto))
        this->desmontar_particion();
}

bool unmount::verificar_id(std::string texto)
{
    /**
     * >(I|i)(D|d)=([a-zA-Z0-9_]+)
     */
    if (std::regex_search(texto, std::regex(">(I|i)(D|d)=([a-zA-Z0-9_]+)")))
    {
        this->id = this->split_text_unmount(texto, '=', 2);
        return true;
    }
    else
    {
        return false;
        std::cout << "Error: el id no es valido" << std::endl;
    }
}

void unmount::desmontar_particion()
{
    std::cout << "Desmount completo" << std::endl;
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
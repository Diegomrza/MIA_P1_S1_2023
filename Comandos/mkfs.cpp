#include "../DefinicionClases/mkfs.h"

void mkfs::analizador_mkfs(std::string texto)
{
    bool bandera, bandera2, bandera3 = true;
    if (this->verificar_id_mkfs(texto) == true)
    {
    }
}

//
bool mkfs::verificar_id_mkfs(std::string texto)
{
    /**
     * >(I|i)(D|d)=[a-zA-Z0-9_]+
     */
    if (std::regex_search(texto, std::regex(">(I|i)(D|d)=[a-zA-Z0-9_]+")))
    {
        this->id = this->split_mkfs(texto, '=', 2);
        return true;
    }
    else
    {
        return false;
    }
}

bool mkfs::verificar_tipo_mkfs(std::string texto)
{
    /**
     * >(T|t)(Y|y)(P|p)(E|e)=(F|f)(U|u)(L|l)(L|l)
     */
    if (std::regex_search(texto, std::regex(">(T|t)(Y|y)(P|p)(E|e)=(F|f)(U|u)(L|l)(L|l)")))
    {
        this->type = "Full";
        return true;
    }
    else
    {
        return false;
    }
}

bool mkfs::verificar_fs_mkfs(std::string texto)
{
    /**
     * >(F|f)(S|s)=(2(F|f)(S|s)|3(F|f)(S|s))
     */
    std::smatch fs;
    if (std::regex_search(texto, fs, std::regex(">(F|f)(S|s)=(2(F|f)(S|s)|3(F|f)(S|s))")))
    {

        this->type = "Full";
        return true;
    }
    else
    {
        return false;
    }
}

//
std::string mkfs::tolower_mkfs(std::string cadena)
{
    std::string aux;
    for (int i = 0; i < cadena.length(); i++)
    {
        aux += tolower(cadena[i]);
    }
    return aux;
}

std::string mkfs::split_mkfs(std::string texto, char delimitador, int posicion)
{
    std::string aux;
    std::stringstream input_stringstream(texto);
    for (int i = 0; i < posicion; i++)
    {
        getline(input_stringstream, aux, delimitador);
    }
    return aux;
}
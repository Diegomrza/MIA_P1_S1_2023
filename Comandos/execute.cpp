#include "../DefinicionClases/execute.h"

// Método principal de la clase execute
void execute::analizador_execute(std::string comando)
{
    std::string ruta = this->reconocer_execute(comando);

    if (ruta.compare("False") == 0)
    {
        std::cout << "Error de comando execute" << std::endl;
        exit(1);
    }

    std::ifstream archivo(ruta, std::ios::in);
    if (archivo.fail())
    {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        archivo.close();
        exit(1);
    }

    std::string texto;
    while (!archivo.eof())
    {
        getline(archivo, texto);
        texto = limpiar_texto(texto);
        if (texto.compare("") != 0)
        {
            this->comandos(texto);
        }
    }
    archivo.close();
}

// Función que reconoce el comando execute y retorna la ruta del archivo
std::string execute::reconocer_execute(std::string texto) // devuelve la ruta
{
    std::string extra = this->toLower_execute(texto); // variable extra del comando en minusculas

    if (std::regex_search(extra, std::regex("execute")) == true)
    {
        std::smatch exec;
        if (std::regex_search(extra, exec, std::regex("path")) == false)
        {
            std::cout << "Error en la ruta." << std::endl;
            return "False";
        }
        return this->split_text(texto, '=', 2);
    }
    return "False";
}

// Función que elimina los saltos de linea, tabulaciones y retornos de carro de una cadena de texto
std::string execute::limpiar_texto(std::string texto)
{
    std::regex saltos("\n|\r|\t");
    return regex_replace(texto, saltos, "");
}

// Función que divide una cadena de texto en base a un delimitador y retorna la posición que se le indique
std::string execute::split_text(std::string texto, char delimitador, int posicion)
{
    std::string aux;
    std::stringstream input_stringstream(texto);
    for (int i = 0; i < posicion; i++)
    {
        getline(input_stringstream, aux, delimitador);
    }
    return aux;
}

// Funcion que convierte una cadena a minusculas y la retorna
std::string execute::toLower_execute(std::string cadena)
{
    std::string aux;
    for (int i = 0; i < cadena.length(); i++)
    {
        aux += tolower(cadena[i]);
    }
    return aux;
}

void execute::comandos(std::string texto)
{
    std::smatch comando;
    std::string aux = this->toLower_execute(texto);
    std::regex_search(aux, comando, std::regex("(mkdisk|fdisk|rep|rmdisk|mount|unmount)")); //|pause|exec|mkfs|login|logout|mkgrp|rmgrp|mkusr|rmusr|chmod|mkfile|cat|rem|edit|ren|mkdir|cp|mv|find|chown|chgrp|loss|recovery

    if (comando.str().compare("mkdisk") == 0)
    {
        mkdisk mk(texto);
        std::cout << std::endl;
    }
    else if (comando.str().compare("fdisk") == 0)
    {
        fdisk fd(texto);
        std::cout << std::endl;
    }
    else if (comando.str().compare("rep") == 0)
    {
        rep re(texto);
        std::cout << std::endl;
    }
    else if (comando.str().compare("rmdisk") == 0)
    {
        rmdisk rm(texto);
        std::cout << std::endl;
    } else if (comando.str().compare("mount") == 0) 
    {
        mount mo(texto);
        std::cout << std::endl;
    } else if (comando.str().compare("unmount") == 0) 
    {
        unmount um(texto);
        std::cout << std::endl;
    }
    else
    {
        std::cout << "No se reconoce algun comando" << std::endl << std::endl;
    }
}

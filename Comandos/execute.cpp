#include "../DefinicionClases/execute.h"

std::string execute::split_text(std::string texto, char delimitador, int posicion)
{
    std::string aux;
    std::stringstream input_stringstream(texto);
    for (int i = 0; i < posicion; i++)
    {
        getline(input_stringstream, aux, delimitador);
    }
    // getline(input_stringstream, aux, '>'); //Lee lo primero y lo guarda
    // getline(input_stringstream, aux, '>'); //Lee lo segundo y lo guarda (reemplaza lo de antes)
    // cout<<"Parámetro extraído: "<<aux<<endl;
    return aux;
}

std::string execute::limpiar_texto(std::string texto)
{
    std::regex saltos("\n|\r|\t");
    return regex_replace(texto, saltos, "");
}

std::string execute::reconocer_execute(std::string texto) // devuelve la ruta
{
    std::smatch ptrn;
    std::regex_search(texto, ptrn, std::regex("execute"));

    if (ptrn.str().compare("execute") == 0)
    {
        std::smatch pth;
        if (std::regex_search(texto, pth, std::regex("path")) == false)
        {
            std::cout << "No viene la ruta" << std::endl;
            return "False";
        }
        return this->split_text(texto, '=', 2);
    }
    return "False";
}

void execute::comandos(std::string texto)
{
    std::smatch comando;
    std::regex_search(texto, comando, std::regex("(mkdisk|fdisk|rep|rmdisk)"));

    if (comando.str().compare("mkdisk") == 0)
    {
        mkdisk mk(texto);
    }
    else if (comando.str().compare("fdisk") == 0)
    {
        fdisk fd(texto);
    }
    else if (comando.str().compare("rep") == 0)
    {
        rep re(texto);
    } else if (comando.str().compare("rmdisk") == 0) 
    {
        rmdisk rm(texto);
    }
    else
    {
        std::cout << "No se reconoce algun comando" << std::endl;
    }
}

void execute::analizador_execute(std::string comando)
{
    std::string ruta = this->reconocer_execute(comando);
    if (ruta.compare("False") != 0)
    {
        std::ifstream archivo(ruta, std::ios::in);
        if (!archivo.fail())
        {
            std::string texto;
            while (!archivo.eof())
            {
                getline(archivo, texto);
                texto = limpiar_texto(texto);
                this->comandos(texto);
            }
        }
        archivo.close();
    } else {
        std::cout<<"Error de comando"<<std::endl;
    }
}

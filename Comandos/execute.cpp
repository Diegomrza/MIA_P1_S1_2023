#include "../DefinicionClases/execute.h"

std::string execute::split_text(std::string texto, char delimitador, int posicion) {
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

std::string execute::quitar_espacios_blanco(std::string texto) {
    std::regex saltos("\n|\r|\t");
    return regex_replace(texto, saltos, ""); 
}

void execute::analizador(std::string comando) {
    std::regex execu("execute");
    std::smatch ext;

    std::regex path(">path");
    std::smatch pt;

    //std::cout << boolalpha;

    if (std::regex_search(comando, ext, execu))
    {
        if (std::regex_search(comando, pt, path))
        {
            std::string ruta = this->split_text(comando, '=', 2);
            std::ifstream archivo(ruta, std::ios::in);

            if (archivo.fail())
            {
                std::cout << "Error" << std::endl;
            }
            else
            {
                std::string texto;
                while (!archivo.eof())
                {
                    getline(archivo, texto);
                    texto = quitar_espacios_blanco(texto);
                    if (texto.compare("mkdisk") == 0)
                    {
                        mkdisk mk("disco.dsk");
                    } else
                    if (texto.compare("rep") == 0)
                    {
                        rep rp("disco.dsk");
                    }
                }
            }

            archivo.close();
        }
        else
        {
            std::cout << "Error comando path" << std::endl;
        }
    }
    else
    {
        std::cout << "Error comando execute" << std::endl;
    }
}


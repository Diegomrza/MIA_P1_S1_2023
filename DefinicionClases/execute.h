#ifndef EXECUTE_H
#define EXECUTE_H

#include <string>
#include <sstream>
#include <regex>
#include <iostream>
#include <fstream>
#include "../Comandos/mkdisk.cpp"
#include "../Comandos/fdisk.cpp"
#include "../Comandos/rep.cpp"

class execute
{
private:
    void analizador_execute(std::string);           // Iniciar la ejecución de validar el comando execute
    std::string limpiar_texto(std::string);         // Quita estos caracteres de la entrada => \n \r \t
    std::string split_text(std::string, char, int); // Separa la cadena recibiendo un delimitador y la posicion que se desea obtener
    std::string reconocer_execute(std::string);     // Valida que si el comando execute viene tambien venga path
    void comandos(std::string);                     // Reconoce todos los posibles comandos que vienen en el archivo ejecutado por el execute

public:
    execute(std::string);
    ~execute();
};

execute::execute(std::string comando)
{
    this->analizador_execute(comando);
}

execute::~execute()
{
}

#endif
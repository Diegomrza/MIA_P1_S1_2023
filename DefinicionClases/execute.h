#ifndef EXECUTE_H
#define EXECUTE_H

#include <string>
#include <sstream>
#include <regex>
#include <iostream>
#include <fstream>
#include "../Comandos/mkdisk.cpp"
#include "../Comandos/rep.cpp"

class execute
{
private:
    /* data */
    void analizador(std::string);
    std::string quitar_espacios_blanco(std::string);
    std::string split_text(std::string, char, int);

public:
    execute(std::string/* args */);
    ~execute();
};

execute::execute(std::string comando/* args */)
{
    this->analizador(comando);
}

execute::~execute()
{
}

#endif
#ifndef UNMOUNT_H
#define UNMOUNT_H

#include <iostream>
#include <string>
#include <regex>

class unmount
{
private:
    std::string id;
    void analizador_unmount(std::string texto);
    std::string toLower_unmount(std::string);
    std::string split_text_unmount(std::string texto, char delimitador, int posicion);
    void desmontar();

public:
    unmount(std::string);
    ~unmount();
};

unmount::unmount(std::string texto)
{
    this->id = "";
    this->analizador_unmount(texto);
}

unmount::~unmount()
{
}


#endif
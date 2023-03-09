#ifndef COMENTARIO_H
#define COMENTARIO_H

#include <string>
#include <regex>

class comentario
{
private:
    std::string comentarios[100];
    int contador_comentarios = 0;
    void analizador_comentario(std::string);

public:
    comentario(std::string);
    ~comentario();
};

comentario::comentario(std::string texto)
{
    this->analizador_comentario(texto);
}

comentario::~comentario()
{
}


#endif
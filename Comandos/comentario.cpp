#include "../DefinicionClases/comentario.h"

void comentario::analizador_comentario(std::string texto) {
    if (std::regex_search(texto, std::regex("#.*"))== true) {
        this->comentarios[this->contador_comentarios] = std::regex_replace(texto, std::regex("#"), "");
        this->contador_comentarios++;
        std::cout<<"Comentario: "<<this->comentarios[this->contador_comentarios-1]<<std::endl;
    }
}


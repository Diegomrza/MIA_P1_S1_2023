#include "../DefinicionClases/comentario.h"

void comentario::analizador_comentario(std::string texto) {
    if (std::regex_search(texto, std::regex("#.*"))== true) {
        this->comentarios[this->contador_comentarios] = this->split_text_comentarios(texto, '#', 2);
        this->contador_comentarios++;
        std::cout<<"Comentario: "<<this->comentarios[this->contador_comentarios-1]<<std::endl;
    }
}

std::string comentario::split_text_comentarios(std::string texto, char delimitador, int posicion) {
    std::string aux;
    std::stringstream input_stringstream(texto);
    for (int i = 0; i < posicion; i++) {
        getline(input_stringstream, aux, delimitador);
    }
    return aux;
}

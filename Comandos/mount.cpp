#include "../DefinicionClases/mount.h"

void mount::analizador_mount(std::string texto)
{
    bool bandera = true;    //path
    bool bandera2 = true;   //name

    std::string aux = this->toLower_mount(texto);

    // Parámetros obligatorios
    (std::regex_search(aux, std::regex(">path"))) ? bandera = this->verificar_ruta(texto) : bandera = false;
    (std::regex_search(aux, std::regex(">name"))) ? bandera2 = this->verificar_nombre(texto) : bandera2 = false;

    if (bandera == true && bandera2 == true) {
        this->montar_particion();
        std::cout<<"\nMount completo"<<std::endl;
        std::cout<<"Ruta: "<<this->ruta<<std::endl;
        std::cout<<"Nombre: "<<this->nombre<<std::endl;
    } else {
        std::cout<<"Error al utilizar el comando mount"<<std::endl;
    }
}

//Parámetros obligatorios
bool mount::verificar_ruta(std::string texto)
{
    std::smatch ru; // Ruta
    /**
     * >(P|p)(A|a)(T|t)(H|h)=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")
    */
    if (std::regex_search(texto, ru, std::regex(">(P|p)(A|a)(T|t)(H|h)=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")"))) {
        this->ruta = this->split_text_mount(ru.str(), '=', 2);
        return true;
    }
    std::cout<<"Error: Ruta no válida"<<std::endl;
    return false;
}

bool mount::verificar_nombre(std::string texto)
{
    std::smatch no; // Nombre
    /**
     * >(N|n)(A|a)(M|m)(E|e)=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")
    */
    if (std::regex_search(texto, no, std::regex(">(N|n)(A|a)(M|m)(E|e)=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")"))) {
        this->nombre = this->split_text_mount(no.str(), '=', 2);
        return true;
    }
    std::cout<<"Error: Nombre no válido"<<std::endl;
    return false;
}

void mount::montar_particion() {

}

std::string mount::toLower_mount(std::string texto)
{
    std::string aux = "";
    for (int i = 0; i < texto.length(); i++) {
        aux += tolower(texto[i]);
    }
    return aux;
}

std::string mount::split_text_mount(std::string texto, char delimitador, int posicion)
{
    std::string aux;
    std::stringstream input_stringstream(texto);
    for (int i = 0; i < posicion; i++)
    {
        getline(input_stringstream, aux, delimitador);
    }
    return aux;
}
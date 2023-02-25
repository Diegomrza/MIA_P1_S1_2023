#include "../DefinicionClases/fdisk.h"

bool fdisk::verify_tamanio(std::string texto) //Obligatorio
{
    std::smatch ta; // Tamaño
    if (std::regex_search(texto, ta, std::regex(">size=[1-9][0-9]*"))) {
        std::cout<<"Tamaño: "<<ta.str()<<std::endl;
        if (stoi(this->split_text_fdisk(ta.str(), '=', 2)) <= 0) {
            return false;
        } else {
            this->tamanio = stoi(this->split_text_fdisk(ta.str(), '=', 2));
            return true;
        }
    } else {
        return false;
    }
}

bool fdisk::verify_ruta(std::string texto) //Obligatorio
{
    std::smatch ru; // Ruta
    
    if (std::regex_search(texto, ru, std::regex(">path=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")"))) {
        std::cout<<"Ruta: "<<ru.str()<<std::endl;
        this->ruta = this->split_text_fdisk(ru.str(), '=', 2);
        return true;
    } else {
        return false;
    }
}

bool fdisk::verify_nombre(std::string texto) //Obligatorio
{
    std::smatch no; // Nombre
    if (std::regex_search(texto, no, std::regex(">name=[a-zA-Z0-9_]+"))) {
        std::cout<<"Nombre: "<<no.str()<<std::endl;
        this->nombre = this->split_text_fdisk(no.str(), '=', 2);
        return true;
    } else {
        return false;
    }
}

bool fdisk::verify_tipo(std::string texto) //Opcional
{
    std::smatch ti; // Tipo
    if (std::regex_search(texto, ti, std::regex(">type=(E|e|L|l|P|p)"))) {
        std::cout<<"Tipo: "<<ti.str()<<std::endl;
        this->tipo = this->split_text_fdisk(ti.str(), '=', 2);
        return true;
    } else {
        return false;
    }
}

bool fdisk::verify_ajuste(std::string texto) //Opcional
{
    std::smatch aj; // Ajuste
    if (std::regex_search(texto, aj, std::regex(">fit=(BF|FF|WF|bf|ff|wf)"))) {
        std::cout<<"Ajuste: "<<aj.str()<<std::endl;
        this->ajuste = this->split_text_fdisk(aj.str(), '=', 2);
        return true;
    } else {
        return false;
    }
}

bool fdisk::verify_eliminar(std::string texto) //Opcional
{
    std::smatch de; // Eliminar
    if (std::regex_search(texto, de, std::regex(">delete="))) {
        std::cout<<"Eliminar: "<<de.str()<<std::endl;
        return true;
    } else {
        return false;
    }
}

bool fdisk::verify_unidades(std::string texto) //Opcional
{
    std::smatch un; // Unidad
    if (std::regex_search(texto, un, std::regex(">unit=(B|K|M|b|k|m)"))) {
        std::cout<<"Unidades: "<<un.str()<<std::endl;
        this->unidades = this->split_text_fdisk(un.str(), '=', 2);
        return true;
    } else {
        return false;
    }
}

void fdisk::analizador_fdisk(std::string texto)
{
    std::cout << "Comando en fdisk: " << texto << std::endl;
    bool bandera = true;

    // Parámetros obligatorios
    (std::regex_search(texto, std::regex(">size"))) ? bandera = this->verify_tamanio(texto) : bandera = false;
    (std::regex_search(texto, std::regex(">path"))) ? bandera = this->verify_ruta(texto) : bandera = false;
    (std::regex_search(texto, std::regex(">name"))) ? bandera = this->verify_nombre(texto) : bandera = false;
    
    // Parámetros opcionales
    if (std::regex_search(texto, std::regex(">type"))) { bandera = this->verify_tipo(texto); }
    if (std::regex_search(texto, std::regex(">unit"))) { bandera = this->verify_unidades(texto); }
    if (std::regex_search(texto, std::regex(">fit"))) { bandera = this->verify_ajuste(texto); }
    if (std::regex_search(texto, std::regex(">delete"))) { bandera = this->verify_eliminar(texto); }

    if (bandera == false) {
        std::cout<<"Error al utilizar el comando fdisk"<<std::endl;
    } else {
        std::cout<<"\nFdisk completo"<<std::endl;
        std::cout<<"Tamaño: "<<this->tamanio<<std::endl;
        std::cout<<"Ruta: "<<this->ruta<<std::endl;
        std::cout<<"Nombre: "<<this->nombre<<std::endl;
        std::cout<<"Tipo: "<<this->tipo<<std::endl;
        std::cout<<"Unidades: "<<this->unidades<<std::endl;
        std::cout<<"Ajuste: "<<this->ajuste<<std::endl;
        this->crear_particion();
    }
    std::cout<<"\n"<<std::endl;
}

void fdisk::crear_particion() {
    structParticion nuevo;
    nuevo.tamanio = this->tamanio;
    strcpy(nuevo.ruta, this->ruta.c_str());
    strcpy(nuevo.nombre, this->nombre.c_str());
    strcpy(nuevo.tipo, this->tipo.c_str());
    strcpy(nuevo.unidades, this->unidades.c_str());
    strcpy(nuevo.ajuste, this->ajuste.c_str());

}

std::string fdisk::split_text_fdisk(std::string texto, char delimitador, int posicion) {
    std::string aux;
    std::stringstream input_stringstream(texto);
    for (int i = 0; i < posicion; i++)
    {
        getline(input_stringstream, aux, delimitador);
    }
    return aux;
}
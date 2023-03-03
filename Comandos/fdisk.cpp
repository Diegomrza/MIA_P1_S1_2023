#include "../DefinicionClases/fdisk.h"

void fdisk::analizador_fdisk(std::string texto)
{
    bool bandera = true;    //path
    bool bandera2 = true;   //name
    bool bandera3 = true;   //size
    bool bandera4 = true;   //type
    bool bandera5 = true;   //unit
    bool bandera6 = true;   //fit
    bool bandera7 = true;   //delete
    bool bandera8 = true;   //add

    std::string aux = this->toLower_fdisk(texto);

    // Parámetros obligatorios
    (std::regex_search(aux, std::regex(">path"))) ? bandera = this->verificar_ruta(texto) : bandera = false;
    (std::regex_search(aux, std::regex(">name"))) ? bandera2 = this->verificar_nombre(texto) : bandera2 = false;
    (std::regex_search(aux, std::regex(">size"))) ? bandera3 = this->verificar_tamanio(texto) : bandera3 = false;
    
    // Parámetros opcionales
    if (std::regex_search(aux, std::regex(">type"))) { bandera4 = this->verificar_tipo(texto); }
    if (std::regex_search(aux, std::regex(">unit"))) { bandera5 = this->verificar_unidades(texto); }
    if (std::regex_search(aux, std::regex(">fit"))) { bandera6 = this->verificar_ajuste(texto); }
    if (std::regex_search(aux, std::regex(">delete"))) { bandera7 = this->verificar_eliminar(texto); }
    if (std::regex_search(aux, std::regex(">add"))) { bandera8 = this->verificar_agregar(texto); }

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
    std::cout<<std::endl;
}

//Parámetros obligatorios
bool fdisk::verificar_ruta(std::string texto)
{
    std::smatch ru; // Ruta
    /**
     * >(P|p)(A|a)(T|t)(H|h)=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")
    */
    if (std::regex_search(texto, ru, std::regex(">(P|p)(A|a)(T|t)(H|h)=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")"))) {
        this->ruta = this->split_text_fdisk(ru.str(), '=', 2);
        return true;
    }
    std::cout<<"Error: Ruta no válida"<<std::endl;
    return false;
}

bool fdisk::verificar_nombre(std::string texto)
{
    std::smatch no; // Nombre
    std::string aux = this->toLower_fdisk(texto);
    /**
     * >(N|n)(A|a)(M|m)(E|e)=[a-zA-Z0-9_]+
    */
    if (std::regex_search(texto, no, std::regex(">(N|n)(A|a)(M|m)(E|e)=[a-zA-Z0-9_]+"))) {
        this->nombre = this->split_text_fdisk(no.str(), '=', 2);
        return true;
    }
    std::cout<<"Error: Nombre no válido"<<std::endl;
    return false;
}

bool fdisk::verificar_tamanio(std::string texto)
{
    std::smatch ta; // Tamaño

    /**
     * >(S|s)(I|i)(Z|z)(E|e)=[1-9][0-9]*
    */
    if (std::regex_search(texto, ta, std::regex(">(S|s)(I|i)(Z|z)(E|e)=[1-9][0-9]*"))) {
        if (stoi(this->split_text_fdisk(ta.str(), '=', 2)) <= 0) {
            return false;
        } else {
            this->tamanio = stoi(this->split_text_fdisk(ta.str(), '=', 2));
            return true;
        }
    }
    std::cout<<"Error: Tamaño no válido"<<std::endl;
    return false;
}

//Parámetros opcionales
bool fdisk::verificar_tipo(std::string texto)
{
    std::smatch ti; // Tipo
    /**
     * >(T|t)(Y|y)(P|p)(E|e)=(E|e|L|l|P|p)
    */
    if (std::regex_search(texto, ti, std::regex(">type=(E|e|L|l|P|p)"))) {
        this->tipo = this->split_text_fdisk(ti.str(), '=', 2);
        return true;
    }
    std::cout<<"Error: Tipo no válido"<<std::endl;
    return false;
}

bool fdisk::verificar_unidades(std::string texto)
{
    std::smatch un; // Unidad
    /**
     * >(U|u)(N|n)(I|i)(T|t)=(B|K|M|b|k|m)
    */
    if (std::regex_search(texto, un, std::regex(">unit=(B|K|M|b|k|m)"))) {
        this->unidades = this->split_text_fdisk(un.str(), '=', 2);
        return true;
    }
    std::cout<<"Error: Unidad no válida"<<std::endl;
    return false;
}

bool fdisk::verificar_ajuste(std::string texto)
{
    std::smatch aj; // Ajuste
    /**
     * >(F|f)(I|i)(T|t)=(B|F|W|b|f|w)(F|f)
    */
    if (std::regex_search(texto, aj, std::regex(">(F|f)(I|i)(T|t)=(B|F|W|b|f|w)(F|f)"))) {
        if (aj.str().compare("BF") == 0 || aj.str().compare("bf") || aj.str().compare("Bf") || aj.str().compare("bF")) {
            this->ajuste = "BF";
        } else if (aj.str().compare("FF") == 0 || aj.str().compare("ff") || aj.str().compare("Ff") || aj.str().compare("fF")) {
            this->ajuste = "FF";
        } else if (aj.str().compare("WF") == 0 || aj.str().compare("wf") || aj.str().compare("Wf") || aj.str().compare("wF")) {
            this->ajuste = "WF";
        }
        return true;
    }
    std::cout<<"Error: Ajuste no válido"<<std::endl;
    return false;
}

bool fdisk::verificar_eliminar(std::string texto)
{
    std::smatch de; // Eliminar
    /**
     * >(D|d)(E|e)(L|l)(E|e)(T|t)(E|e)=(F|f)(U|u)(L|l)(L|l)
    */
    if (std::regex_search(texto, de, std::regex(">(D|d)(E|e)(L|l)(E|e)(T|t)(E|e)=(F|f)(U|u)(L|l)(L|l)"))) {
        this->eliminar = "FULL";
        return true;
    }
    std::cout<<"Error: Eliminar no válido"<<std::endl;
    return false;
}

bool fdisk::verificar_agregar(std::string texto) {
    std::smatch ad; //Agregar
    /**
     * >(A|a)(D|d)(D|d)=(\\d+|-\\d+)
    */
    if (std::regex_search(texto, ad, std::regex(">(A|a)(D|d)(D|d)=(\\d+|-\\d+)"))) {
        this->agregar = this->split_text_fdisk(texto, '=', 2);
        return true;
    }
    std::cout<<"Error: Agregar no válido"<<std::endl;
    return false;
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

std::string fdisk::toLower_fdisk(std::string texto) {
    std::string aux;
    for (int i = 0; i < texto.length(); i++) {
        aux += tolower(texto[i]);
    }
    return aux;
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
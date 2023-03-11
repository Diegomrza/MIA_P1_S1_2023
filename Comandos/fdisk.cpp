#include "../DefinicionClases/fdisk.h"

void fdisk::analizador_fdisk(std::string texto)
{
    bool bandera = true;  // path
    bool bandera2 = true; // name
    bool bandera3 = true; // size
    bool bandera4 = true; // type
    bool bandera5 = true; // unit
    bool bandera6 = true; // fit
    bool bandera7 = true; // delete
    bool bandera8 = true; // add

    std::string aux = this->toLower_fdisk(texto);

    // Parámetros obligatorios
    (std::regex_search(aux, std::regex(">path"))) ? bandera = this->verificar_ruta(texto) : bandera = false;
    (std::regex_search(aux, std::regex(">name"))) ? bandera2 = this->verificar_nombre(texto) : bandera2 = false;
    //(std::regex_search(aux, std::regex(">size"))) ? bandera3 = this->verificar_tamanio(texto) : bandera3 = false;

    // Parámetros opcionales
    if (std::regex_search(aux, std::regex(">size"))) bandera3 = this->verificar_tamanio(texto);
    if (std::regex_search(aux, std::regex(">type"))) bandera4 = this->verificar_tipo(texto);
    if (std::regex_search(aux, std::regex(">unit"))) bandera5 = this->verificar_unidades(texto);
    if (std::regex_search(aux, std::regex(">fit"))) bandera6 = this->verificar_ajuste(texto);

    //Leyendo comentario si hubiera
    if (std::regex_search(texto, std::regex("#"))) comentario co(texto);
    
    //delete => name y path tienen que venir
    if (std::regex_search(aux, std::regex(">delete"))) bandera7 = this->verificar_eliminar(texto);
    
    //add => unit tiene que venir
    if (std::regex_search(aux, std::regex(">add"))) bandera8 = this->verificar_agregar(texto);
    
    if (   bandera == false 
        || bandera2 == false 
        || bandera3 == false 
        || bandera4 == false 
        || bandera5 == false 
        || bandera6 == false 
        || bandera7 == false 
        || bandera8 == false
        ) {
        std::cout << "Error al utilizar el comando fdisk." << std::endl;
    } else {
        std::cout << "\nFdisk completo" << std::endl;
        std::cout << "Tamaño: " << this->tamanio << std::endl;
        std::cout << "Ruta: " << this->ruta << std::endl;
        std::cout << "Nombre: " << this->nombre << std::endl;
        std::cout << "Tipo: " << this->tipo << std::endl;
        std::cout << "Unidades: " << this->unidades << std::endl;
        std::cout << "Ajuste: " << this->ajuste << std::endl;
        this->crear_particion();
    }
    std::cout << std::endl;
}

// Parámetros obligatorios
bool fdisk::verificar_ruta(std::string texto) {
    std::smatch ru; // Ruta
    /**
     * >(P|p)(A|a)(T|t)(H|h)=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")
     */
    if (std::regex_search(texto, ru, std::regex(">(P|p)(A|a)(T|t)(H|h)=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")"))) {
        this->ruta = this->split_text_fdisk(regex_replace(ru.str(), std::regex("\""), ""), '=', 2);
        return true;
    }
    std::cout << "Error: Ruta no válida" << std::endl;
    return false;
}

bool fdisk::verificar_nombre(std::string texto) {
    std::smatch no; // Nombre
    /**
     * >(N|n)(A|a)(M|m)(E|e)=[a-zA-Z0-9_]+
     */
    if (std::regex_search(texto, no, std::regex(">(N|n)(A|a)(M|m)(E|e)=[a-zA-Z0-9_]+"))) {
        this->nombre = this->split_text_fdisk(no.str(), '=', 2);
        return true;
    }
    std::cout << "Error: Nombre no válido" << std::endl;
    return false;
}

bool fdisk::verificar_tamanio(std::string texto) {
    std::smatch ta; // Tamaño
    /**
     * >(S|s)(I|i)(Z|z)(E|e)=[1-9][0-9]*
     */
    if (std::regex_search(texto, ta, std::regex(">(S|s)(I|i)(Z|z)(E|e)=(-)?[0-9]+"))) {
        int numero = stoi(this->split_text_fdisk(ta.str(), '=', 2));
        if (numero < 0) { // Tamaño negativo
            std::cout << "Error: El tamaño no debe ser negativo. " << std::endl;
            return false;
        } else if (numero == 0) { // Tamaño igual a 0
            std::cout << "Error: El tamaño debe ser mayor a 0. " << std::endl;
            return false;
        } else {
            this->tamanio = numero;
            return true;
        }
    }
    std::cout << "Error: Tamaño no válido" << std::endl;
    return false;
}

// Parámetros opcionales
bool fdisk::verificar_tipo(std::string texto) {
    std::smatch ti; // Tipo
    /**
     * >(T|t)(Y|y)(P|p)(E|e)=(E|e|L|l|P|p)
     */
    if (std::regex_search(texto, ti, std::regex(">type=(E|e|L|l|P|p)"))) {
        std::string aux = this->toLower_fdisk(this->split_text_fdisk(ti.str(), '=', 2));
        if (aux.compare("e") == 0) {
            this->tipo = "E";
        } else if (aux.compare("l") == 0) {
            this->tipo = "L";
        } else if (aux.compare("p") == 0) {
            this->tipo = "P";
        }
        return true;
    }
    std::cout << "Error: Tipo no válido." << std::endl;
    return false;
}

bool fdisk::verificar_unidades(std::string texto)
{
    std::smatch un; // Unidad
    /**
     * >(U|u)(N|n)(I|i)(T|t)=(B|K|M|b|k|m)
     */
    if (std::regex_search(texto, un, std::regex(">unit=(B|K|M|b|k|m)")))
    {
        std::string aux = this->toLower_fdisk(this->split_text_fdisk(un.str(), '=', 2));
        if (aux.compare("b") == 0) {
            this->unidades = "B";
        } else if (aux.compare("k") == 0) {
            this->unidades = "K";
        } else if (aux.compare("m") == 0) {
            this->unidades = "M";
        }
        return true;
    }
    std::cout << "Error: Unidad no válida" << std::endl;
    return false;
}

bool fdisk::verificar_ajuste(std::string texto)
{
    std::smatch aj; // Ajuste
    /**
     * >(F|f)(I|i)(T|t)=(B|F|W|b|f|w)(F|f)
     */
    if (std::regex_search(texto, aj, std::regex(">(F|f)(I|i)(T|t)=(B|F|W|b|f|w)(F|f)")))
    {
        std::string aux = this->toLower_fdisk(this->split_text_fdisk(aj.str(), '=', 2));
        if (aux.compare("bf") == 0) {
            this->ajuste = "BF";
        } else if (aux.compare("ff") == 0) {
            this->ajuste = "FF";
        } else if (aux.compare("wf") == 0) {
            this->ajuste = "WF";
        }
        return true;
    }
    std::cout << "Error: Ajuste no válido" << std::endl;
    return false;
}

bool fdisk::verificar_eliminar(std::string texto)
{
    std::smatch de; // Eliminar
    /**
     * >(D|d)(E|e)(L|l)(E|e)(T|t)(E|e)=(F|f)(U|u)(L|l)(L|l)
     */
    if (std::regex_search(texto, de, std::regex(">(D|d)(E|e)(L|l)(E|e)(T|t)(E|e)=(F|f)(U|u)(L|l)(L|l)")))
    {
        this->eliminar = "FULL";
        return true;
    }
    std::cout << "Error: Eliminar no válido" << std::endl;
    return false;
}

bool fdisk::verificar_agregar(std::string texto)
{
    std::smatch ad; // Agregar
    /**
     * >(A|a)(D|d)(D|d)=(\\d+|-\\d+)
     */
    if (std::regex_search(texto, ad, std::regex(">(A|a)(D|d)(D|d)=(-)?[0-9]+")))
    {   
        int aux = stoi(this->split_text_fdisk(ad.str(), '=', 2));
        if (aux == 0) {
            std::cout << "Error: El tamaño no debe ser 0. " << std::endl;
            return false;
        } 
        this->agregar = aux;
        return true;
    }
    std::cout << "Error: Agregar no válido" << std::endl;
    return false;
}

//
void fdisk::administrador_fdisk() {     
    /*
        [path, name]                 Obligatorio
        (unit, type, fit, size)      Opcionales
        {delete, add}                Opcionales especiales

        Reglas:
        1. Si se va crear una partición tiene que venir además del path y el name, el size.
        2. El parámetro delete tiene mayor precedencia que el add.
        3. El parámetro add va enlazado con la unidad.
    */
    if (this->eliminar.compare("") != 0) { // delete
        this->eliminar_particion();
    } else if (this->agregar != 0) { // add
        //this->modificar_particion();
    } else { // make 
        this->crear_particion();
    }
}

void fdisk::crear_particion() {
    /**
     * Pasos:
     *  1. Verificar si existe el disco. Listo
     *  2. Buscar si existe una particion primaria con ese nombre.
     *  3. Buscar si existe una particion extendida y verificar si tiene ese nombre.
     *  4. Si existe la particion extendida, verificar si existe una particion logica dentro con ese nombre.
     *  5. 
    */
    FILE *arch = fopen(this->ruta.c_str(), "rb");
    MBR mbr;
    if (arch == NULL) {
        std::cout << "Error: No existe el disco." << std::endl;
        return;
    }

    fread(&mbr, sizeof(MBR), 1, arch);
    while (!feof(arch)) {
        if (mbr.mbr_size != 0) {
            structParticion aux = {'0', this->tipo[0], this->ajuste[0], 0, this->tamanio};
            strcpy(aux.part_name, this->nombre.c_str());
            
            if (strcmp(mbr.mbr_partition1.part_name, "") == 0) {

            } else if (strcmp(mbr.mbr_partition2.part_name, "") == 0) {
                
            } else if (strcmp(mbr.mbr_partition3.part_name, "") == 0) {
                
            } else if (strcmp(mbr.mbr_partition4.part_name, "") == 0) {
               
            } else {
                std::cout << "No se puede crear otra partición primaria." << std::endl;
            }
            this->reescribir_mbr(mbr);
            this->mostrar_mbr();
            break;
        }
        fread(&mbr, sizeof(MBR), 1, arch);
    }
    fclose(arch);
}

void fdisk::crear_particion_primaria(MBR mbr) {
    int contador_primarias = this->contador_particiones_primarias(mbr);
    if (contador_primarias == 3 and this->tipo.compare("P") == 0) {
        std::cout << "Error: Ya existen 3 particiones primarias." << std::endl;
        return;
    }
}

void fdisk::crear_particion_extendida(MBR mbr) {

}

void fdisk::crear_particion_logica(MBR mbr) {
    if (!this->existe_particion_extendida(mbr)) {
        std::cout << "Error: No existe una partición extendida." << std::endl;
        return;
    }

}

void fdisk::eliminar_particion() {
    // Busqueda de la partición que se desea eliminar.
    FILE *arch = fopen(this->ruta.c_str(), "rb");
    MBR mbr;
    if (arch == NULL) {
        std::cout << "Error: No existe el disco." << std::endl;
        return;
    }
    fread(&mbr, sizeof(MBR), 1, arch);
    while (!feof(arch)) {
        if (mbr.mbr_size != 0) {
            structParticion aux;
            if (strcmp(this->nombre.c_str(), mbr.mbr_partition1.part_name) == 0) {
                mbr.mbr_partition1 = aux;
            } else if (strcmp(this->nombre.c_str(), mbr.mbr_partition2.part_name) == 0) {
                mbr.mbr_partition2 = aux;
            } else if (strcmp(this->nombre.c_str(), mbr.mbr_partition3.part_name) == 0) {
                mbr.mbr_partition3 = aux;
            } else if (strcmp(this->nombre.c_str(), mbr.mbr_partition4.part_name) == 0) {
                mbr.mbr_partition4 = aux;
            } else {
                std::cout << "Error: La partición que desea eliminar no existe en este disco ." << std::endl;
                return;
            }
            this->reescribir_mbr(mbr);
            break;
        }
    }
}

void fdisk::modificar_particion(structParticion &particion) {
    particion.part_status = '0';
    particion.part_type = this->tipo[0];
    particion.part_fit = this->ajuste[0];
    particion.part_start = 0;
    particion.part_s = this->tamanio;
    strcpy(particion.part_name, this->nombre.c_str());
}

void fdisk::reescribir_mbr(MBR mbr)
{
    std::fstream archivo(this->ruta, std::ios::out | std::ios::in | std::ios::binary);
    if (archivo.is_open())
    {
        archivo.seekp(0);
        archivo.write((char *)&mbr, sizeof(MBR));
        archivo.close();
    }
}

void fdisk::mostrar_mbr() {
    FILE *arch;
    arch = fopen(ruta.c_str(), "rb");
    if (arch == NULL) {
        std::cout << "Error al leer el mbr." << std::endl;
        return;
    }
    MBR mbr;
    std::cout << "Despues de insertar el mbr: " << std::endl;
    fread(&mbr, sizeof(MBR), 1, arch);
    while (!feof(arch))
    {
        if (mbr.mbr_size != 0)
        {
            std::cout << "\nParticion 1: " << std::endl;
            this->mostrar_particion(mbr.mbr_partition1);
            std::cout << "\nParticion 2: " << std::endl;
            this->mostrar_particion(mbr.mbr_partition2);
            std::cout << "\nParticion 3: " << std::endl;
            this->mostrar_particion(mbr.mbr_partition3);
            std::cout << "\nParticion 4: " << std::endl;
            this->mostrar_particion(mbr.mbr_partition4);
        }
        fread(&mbr, sizeof(MBR), 1, arch);
    }
    fclose(arch);
}

void fdisk::mostrar_particion(structParticion particion) {
    std::cout << "Status: " << particion.part_status << std::endl;
    std::cout << "Type: " << particion.part_type << std::endl;
    std::cout << "Fit: " << particion.part_fit << std::endl;
    std::cout << "Start: " << particion.part_start << std::endl;
    std::cout << "Size: " << particion.part_s << std::endl;
    std::cout << "Name: " << particion.part_name << std::endl;
}

int fdisk::contador_particiones_primarias(MBR mbr) {
    int contador = 0;
    if (mbr.mbr_partition1.part_type == 'P')
        contador++;
    
    if (mbr.mbr_partition2.part_type == 'P') 
        contador++;
    
    if (mbr.mbr_partition3.part_type == 'P') 
        contador++;
    
    if (mbr.mbr_partition4.part_type == 'P')
        contador++;
    
    return contador;
}

bool fdisk::existe_particion_extendida(MBR mbr) {
    if (mbr.mbr_partition1.part_type == 'E') {
        return true;
    } else if (mbr.mbr_partition2.part_type == 'E') {
        return true;
    } else if (mbr.mbr_partition3.part_type == 'E') {
        return true;
    } else if (mbr.mbr_partition4.part_type == 'E'){
        return true;
    }
    return false;
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
    for (int i = 0; i < posicion; i++) {
        getline(input_stringstream, aux, delimitador);
    }
    return aux;
}
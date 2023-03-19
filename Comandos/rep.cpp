#include "../DefinicionClases/rep.h"

void rep::analizador_rep(std::string texto) {
    std::cout<<"Comando en rep: "<<texto<<std::endl;
    //name, path, id, ruta

    bool bandera = true;
    bool bandera2 = true;
    bool bandera3 = true;
    bool bandera4 = true;

    std::string aux = this->toLower_rep(texto);

    (std::regex_search(aux, std::regex(">name"))) ? bandera = this->verificar_name(texto) : bandera = false;
    (std::regex_search(aux, std::regex(">path"))) ? bandera2 = this->verificar_path(texto) : bandera2 = false;
    (std::regex_search(aux, std::regex(">id"))) ? bandera3 = this->verificar_id(texto) : bandera3 = false;
    if (std::regex_search(aux, std::regex(">ruta"))) bandera4 = this->verificar_ruta(texto);

    if (bandera == false || bandera2 == false || bandera3 == false || bandera4 == false) {
        std::cout << "Error: faltan parámetros obligatorios." << std::endl;
        return;
    }
    std::cout << "name: " << this->name << std::endl;
    std::cout << "path: " << this->path << std::endl;
    std::cout << "id: " << this->id << std::endl;
    std::cout << "ruta: " << this->ruta << std::endl;

    this->administrador_rep(this->name);
}

void rep::administrador_rep(std::string tipo_reporte) {
    //Grafo g();
    if (tipo_reporte=="MBR") {

    } else if (tipo_reporte=="DISK") {

    } else if (tipo_reporte=="INODE") {

    } else if (tipo_reporte=="JOURNALING") {

    } else if (tipo_reporte=="BLOCK") {

    } else if (tipo_reporte=="BM_INODE") {

    } else if (tipo_reporte=="BM_BLOCK") {

    } else if (tipo_reporte=="TREE") {

    } else if (tipo_reporte=="SB") {

    } else if (tipo_reporte=="FILE") {

    } else if (tipo_reporte=="LS") {

    }
}

bool rep::verificar_name(std::string texto) {
    std::smatch na;
    /**
     * >(N|n)(A|a)(M|m)(E|e)=\"(mbr|disk|inode|journaling|block|bm_inode|bm_block|tree|sb|file|ls)\"
    */
    std::string aux = this->toLower_rep(texto);

    if (std::regex_search(aux, na, std::regex(">name=(mbr|disk|inode|journaling|block|bm_inode|bm_block|tree|sb|file|ls)"))) {
        this->name = this->toUpper_rep(this->split_text_rep(na.str(), '=', 2));
        return true;
    }
    std::cout << "Error: el nombre no cumple." << std::endl;
    return false;

}

bool rep::verificar_path(std::string texto) {
    std::smatch pa;
    /**
     * >(P|p)(A|a)(T|t)(H|h)=((/\\w+)+\\.(png|jpg|pdf)|\"(/(\\w[ ]?)+)+\\.(png|jpg|pdf)\"|\\w+\\.(png|jpg|pdf)|\"(\\w[ ]?)+\\.(png|jpg|pdf)\")
    */

    if (std::regex_search(texto, pa, std::regex(">(P|p)(A|a)(T|t)(H|h)=((/\\w+)+\\.(png|jpg|pdf)|\"(/(\\w[ ]?)+)+\\.(png|jpg|pdf)\"|\\w+\\.(png|jpg|pdf)|\"(\\w[ ]?)+\\.(png|jpg|pdf)\")"))) {
        this->path = this->split_text_rep(pa.str(), '=', 2);
        return true;
    }
    std::cout << "Error: el path no cumple ." << std::endl;
    return false;
}

bool rep::verificar_id(std::string texto) {
    std::smatch id;
    /**
     * >(I|i)(D|d)=\\d+[\w+]
    */

    if (std::regex_search(texto, id, std::regex(">(I|i)(D|d)=\\d+[\\w+]"))) {
        this->id = this->split_text_rep(id.str(), '"', 2);
        return true;
    } 
    std::cout << "Error: el id no cumple." << std::endl;
    return false;
}

bool rep::verificar_ruta(std::string texto) {

    std::smatch ru;
    /**
     * >(R|r)(U|u)(T|t)(A|a)=((/\\w+)+\\.(txt|jpg)|\"(/(\\w[ ]?)+)+\\.(txt|jpg)\"|\\w+\\.(txt|jpg)|\"(\\w[ ]?)+\\.(txt|jpg)\")
    */

    if (std::regex_search(texto, ru, std::regex(">(R|r)(U|u)(T|t)(A|a)=((/\\w+)+\\.(txt|jpg)|\"(/(\\w[ ]?)+)+\\.(txt|jpg)\"|\\w+\\.(txt|jpg)|\"(\\w[ ]?)+\\.(txt|jpg)\")"))) {
        this->ruta = this->split_text_rep(ru.str(), '=', 2);
        return true;
    }
    std::cout << "Error: la ruta no cumple." << std::endl;
    return false;
}

std::string rep::split_text_rep(std::string texto, char delimitador, int posicion) {
    std::string aux;
    std::stringstream input_stringstream(texto);
    for (int i = 0; i < posicion; i++) {
        getline(input_stringstream, aux, delimitador);
    }
    return aux;
}

std::string rep::toLower_rep(std::string texto) {
    std::string aux = "";
    for (int i = 0; i < texto.length(); i++) {
        aux += tolower(texto[i]);
    }
    return aux;
}

std::string rep::toUpper_rep(std::string texto) {
    std::string aux = "";
    for (int i = 0; i < texto.length(); i++) {
        aux += toupper(texto[i]);
    }
    return aux;
}

void rep::mostrar(std::string ruta) {
    
    std::fstream p(ruta, std::ios::out | std::ios::in | std::ios::binary);
    MBR auxP;

    if (p.is_open()) {
        p.read((char *)&auxP, sizeof(auxP));
        while (!p.eof()) {
            if (auxP.mbr_size != 0) {
                std::cout << "Tamanio: " << auxP.mbr_size;
                std::cout << "   Numero: " << auxP.mbr_dsk_signature;
                std::cout << "   Fecha: " << std::ctime(&auxP.mbr_date_creation);
                std::cout << std::endl;
            }

            p.read((char *)&auxP, sizeof(auxP));
        }

        p.close();
    }
}


#include "../DefinicionClases/mkdisk.h"

std::string mkdisk::split_text_mkdisk(std::string texto, char delimitador, int posicion)
{
    std::string aux;
    std::stringstream input_stringstream(texto);
    for (int i = 0; i < posicion; i++)
    {
        getline(input_stringstream, aux, delimitador);
    }
    return aux;
}

bool mkdisk::verify_tamanio_mkdisk(std::string texto) {
    std::smatch tm;
    if (std::regex_search(texto, tm, std::regex(">size=[1-9][0-9]*")) == true) {
        this->tamanio = stoi(this->split_text_mkdisk(tm.str(), '=', 2));
        return true;
    } else {
        std::cout << this->errores_mkdisk(3) << std::endl;
        return false;
    }
}

bool mkdisk::verify_unidades_mkdisk(std::string texto) {
    std::smatch un;
    if (std::regex_search(texto, un, std::regex(">unit=(M|K|m|k)")) == true) {
        if (un.str().compare(">unit=K") == 0 || un.str().compare(">unit=k") == 0) {
            this->unidades = "K";
        } else if (un.str().compare(">unit=M") == 0 || un.str().compare(">unit=m") == 0) {
            this->unidades = "M";
        } else {
            std::cout << this->errores_mkdisk(4) << std::endl;
            return false;
        }
    }
    return true;
}

bool mkdisk::verify_ruta_mkdisk(std::string texto) {
    std::smatch ru;
    if (std::regex_search(texto, ru, std::regex(">path=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")")) == true) {
        this->ruta = this->split_text_mkdisk(ru.str(), '=', 2);
        return true;
    } else {
        std::cout << this->errores_mkdisk(5) << std::endl;
        return false;
    }
}

void mkdisk::analizador_mkdisk(std::string texto)
{
    std::cout << "Comando mkdisk: " << texto << std::endl;
    bool bandera = true; // si es falsa no se creará el disco
    (std::regex_search(texto, std::regex(">size"))) ? bandera = this->verify_tamanio_mkdisk(texto): bandera = false;
    (std::regex_search(texto, std::regex(">path"))) ? bandera = this->verify_ruta_mkdisk(texto): bandera = false;
    (bandera == true) ? this->crear_disco(this->ruta, this->tamanio, this->unidades): this->mensaje_error_crear_disco();
}

void mkdisk::mensaje_error_crear_disco() {
    std::cout << "No se pudo crear el disco" << std::endl;
}

void mkdisk::crear_disco(std::string ruta, int tamanio, std::string unidad)
{
    std::string directorio = regex_replace(ruta, std::regex("\\w+\\.dsk"), "");
    if(mkdir(directorio.c_str(), 0777)!= 0){
        std::cout<<"Error al crear el directorio en: "<<directorio<<std::endl;
        return;
    }

    std::FILE *fichero = fopen(ruta.c_str(), "w+b");
    if (fichero != NULL)
    {
        char ch = '\0';

        int kilobyte = 1000;

        if (unidad.compare("M") == 0)
        {
            kilobyte = kilobyte * 1000;
        }

        for (int i = 0; i < 1000 * 1000 * 5; i++)
        {
            // fwrite(&ch, 1, 1, fichero);
            fwrite(&ch, 1, 1, fichero);
        }

        /*
        Obteniendo la hora
        */
        auto now = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(now);

        MBR mbr1;
        mbr1.mbr_tamano = 5000000;
        mbr1.mbr_dsk_signature = this->numero_random();
        mbr1.mbr_fecha_creacion = end_time;

        this->escribir_mbr(ruta, mbr1);
    }
}

int mkdisk::numero_random()
{
    int numero;
    std::srand(time(NULL));
    numero = 1 + rand() % (101 - 1);
    return numero;
}

void mkdisk::escribir_mbr(std::string ruta, MBR p)
{
    std::fstream archivo(ruta, std::ios::out | std::ios::in | std::ios::binary);
    if (archivo.is_open())
    {
        archivo.seekp((p.mbr_dsk_signature - 1) * sizeof(MBR));
        archivo.write((char *)&p, sizeof(MBR));
        archivo.close();
    }
}

std::string mkdisk::errores_mkdisk(int tipo_error)
{
    switch (tipo_error)
    {
    case 1:
        return "Error, unidad de tamaño negativo";
    case 2:
        return "Error, la unidad debe ser un entero";
    case 3:
        return "Error, el tamaño no viene incluído de manera correcta";
    case 4:
        return "Error, la unidad debe ser el valor de K o M";
    case 5:
        return "Error, la ruta no viene incluida";
    default:
        return "";
    }
}
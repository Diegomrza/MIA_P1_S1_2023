#include "../DefinicionClases/mkdisk.h"

std::string mkdisk::split_text_mkdisk(std::string texto, char delimitador, int posicion) {
    std::string aux;
    std::stringstream input_stringstream(texto);
    for (int i = 0; i < posicion; i++)
    {
        getline(input_stringstream, aux, delimitador);
    }
    // getline(input_stringstream, aux, '>'); //Lee lo primero y lo guarda
    // getline(input_stringstream, aux, '>'); //Lee lo segundo y lo guarda (reemplaza lo de antes)
    // cout<<"Parámetro extraído: "<<aux<<endl;
    return aux;
}

void mkdisk::analizador_mkdisk(std::string texto) {
    std::cout<<"Comando en mkdisk: "<<texto<<std::endl;

    std::smatch tm; //tamaño
    std::smatch un; //unidad
    std::smatch ru; //ruta
    
    if (std::regex_search(texto, tm, std::regex(">size=[0-9]+")) == true) {
        std::cout<<"Size: "<<tm.str()<<std::endl;
    } else {
        std::cout<<"size obligatorio"<<std::endl;
    }

    if (std::regex_search(texto, un, std::regex(">unit")) == true) {
        if (std::regex_search(texto, un, std::regex(">unit=(M|K|m|k)")) == true) {
            if(un.str().compare(">unit=M") == 0 || un.str().compare(">unit=m") == 0) {
                std::cout<<"Unit: M"<<std::endl;
            } else {
                std::cout<<"Unit: K"<<std::endl;
            }
        } else {
            std::cout<<"Error de unidad, debe ser => M ó K"<<std::endl;
        }
    } else {
        std::cout<<"Unit: M"<<std::endl;
    }
    
    //  "([/]?\w[  ]?)+/(\w[ ]?)+\.dsk"

    if (std::regex_search(texto, ru, std::regex(">path=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")")) == true) {
        std::cout<<"Ruta: "<<this->split_text_mkdisk(ru.str(), '=', 2)<<std::endl;
    } else {
        std::cout<<"path obligatorio"<<std::endl;
    }
    std::cout<<"\n"<<std::endl;
}

void mkdisk::crear_disco(std::string ruta)
{
    std::FILE *fichero = fopen(ruta.c_str(), "w+b");
    char ch = '\0';

    for (int i = 0; i < 1024 * 1024 * 5; i++)
    {
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

int mkdisk::numero_random()
{
    // int numero = rand() % 100 + 1;
    int numero = rand() % 100+1;
    return numero;
}

void mkdisk::escribir_mbr(std::string ruta, MBR p) {
    std::fstream archivo(ruta, std::ios::out | std::ios::in | std::ios::binary);
    if (archivo.is_open())
    {
        archivo.seekp((p.mbr_dsk_signature - 1) * sizeof(MBR));
        archivo.write((char *)&p, sizeof(MBR));
        archivo.close();
    }
}

#include "../DefinicionClases/mkdisk.h"

void mkdisk::crear_disco(std::string ruta)
{
    std::cout<<"Simon"<<std::endl;
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

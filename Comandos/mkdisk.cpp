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

void mkdisk::analizador_mkdisk(std::string texto)
{
    std::cout << "Comando mkdisk: " << texto << std::endl;
    std::smatch tm; // tamaño
    std::smatch un; // unidad
    std::smatch ru; // ruta

    bool bandera = true; // si es falsa no se creará el disco

    if (std::regex_search(texto, un, std::regex(">unit=(M|K|m|k)")) == true)
    {
        
        if (un.str().compare(">unit=K") == 0 || un.str().compare(">unit=k") == 0)
        {
            this->unidades = "K";
        }
        else if (un.str().compare(">unit=M") == 0 || un.str().compare(">unit=m") == 0)
        {
            this->unidades = "M";
        }
        else
        {
            std::cout << this->errores_mkdisk(4) << std::endl;
            bandera = false;
        }
    }

    if (std::regex_search(texto, tm, std::regex(">size=[1-9][0-9]*")) == true)
    {
        // std::cout << "Size: " << stoi(tm.str()) << std::endl;
        this->tamanio = stoi(this->split_text_mkdisk(tm.str(), '=', 2));
        if (std::regex_search(texto, ru, std::regex(">path=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")")) == true)
        {
            std::cout << "Ruta: " << this->split_text_mkdisk(ru.str(), '=', 2) << std::endl;
            this->ruta = this->split_text_mkdisk(ru.str(), '=', 2);
        }
        else
        {
            std::cout << this->errores_mkdisk(5) << std::endl;
            bandera = false;
        }
    }
    else
    {
        std::cout << this->errores_mkdisk(3) << std::endl;
        bandera = false;
    }

    if (bandera)
    {
        this->crear_disco(this->ruta, this->tamanio, this->unidades);
    }
    else
    {
        std::cout << "No se pudo crear el disco" << std::endl;
    }
}

void mkdisk::crear_disco(std::string ruta, int tamanio, std::string unidad)
{
    std::string directorio = regex_replace(ruta, std::regex("\\w+\\.dsk"), "");
    std::cout<<mkdir(directorio.c_str(), 0777)<<std::endl;

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
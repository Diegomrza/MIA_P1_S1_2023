#include "../DefinicionClases/mkdisk.h"

void mkdisk::analizador_mkdisk(std::string texto)
{
    bool bandera = true;  // size => obligatorio
    bool bandera2 = true; // path => obligatorio
    bool bandera3 = true; // fit => opcional
    bool bandera4 = true; // unit => opcional

    std::string aux = this->tolower_mkdisk(texto); // Variable con el comando en minusculas

    (std::regex_search(aux, std::regex(">path"))) ? bandera2 = this->verificar_ruta_mkdisk(texto) : bandera2 = false;
    (std::regex_search(aux, std::regex(">size"))) ? bandera = this->verificar_tamanio_mkdisk(texto) : bandera = false;
    if (std::regex_search(aux, std::regex(">fit")))
        bandera3 = this->verificar_fit_mkdisk(texto);
    if (std::regex_search(aux, std::regex(">unit")))
        bandera4 = this->verificar_unidades_mkdisk(texto);

    if ((bandera == true) && (bandera2 == true) && (bandera3 == true) && (bandera4 == true))
    {
        this->crear_disco(this->ruta, this->tamanio, this->unidades);
    }
    else
    {
        std::cout << "No se pudo crear el disco" << std::endl;
    }
}

/*  Funciones para verificar    */
bool mkdisk::verificar_ruta_mkdisk(std::string texto)
{
    std::smatch ru;
    if (std::regex_search(texto, ru, std::regex("=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")")) == true)
    {
        this->ruta = this->split_text_mkdisk(regex_replace(ru.str(), std::regex("\""), ""), '=', 2);
        return true;
    }
    std::cout << this->errores_mkdisk(1) << std::endl;
    return false;
}

bool mkdisk::verificar_tamanio_mkdisk(std::string texto)
{
    std::smatch tm;
    std::string aux = this->tolower_mkdisk(texto);
    if (std::regex_search(aux, tm, std::regex(">size=[1-9][0-9]*")) == true)
    {
        this->tamanio = stoi(this->split_text_mkdisk(tm.str(), '=', 2));
        return true;
    }
    std::cout << this->errores_mkdisk(2) << std::endl;
    return false;
}

bool mkdisk::verificar_fit_mkdisk(std::string texto)
{
    std::smatch ft;
    std::string aux = this->tolower_mkdisk(texto);

    if (std::regex_search(aux, ft, std::regex(">fit=(ff|bf|wf)")) == true)
    {
        if (ft.str().compare("ff") == 0)
        {
            this->fit = "FF";
        }
        else if (ft.str().compare("bf") == 0)
        {
            this->fit = "BF";
        }
        else
        {
            this->fit = "WF";
        }
        return true;
    }
    std::cout << this->errores_mkdisk(3) << std::endl;
    return false;
}

bool mkdisk::verificar_unidades_mkdisk(std::string texto)
{
    std::smatch un;
    std::string aux = this->tolower_mkdisk(texto);

    if (std::regex_search(aux, un, std::regex(">unit=(m|k)")) == true)
    {
        if (un.str().compare(">unit=k") == 0)
        {
            this->unidades = "K";
        }
        else
        {
            this->unidades = "M";
        }
        return true;
    }
    std::cout << this->errores_mkdisk(4) << std::endl;
    return false;
}

//
std::string mkdisk::tolower_mkdisk(std::string texto)
{
    std::string aux;
    for (int i = 0; i < texto.length(); i++)
    {
        aux += tolower(texto[i]);
    }
    return aux;
}

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

int mkdisk::numero_random()
{
    int numero;
    std::srand(time(NULL));
    numero = 1 + rand() % (101 - 1);
    return numero;
}

void mkdisk::crear_disco(std::string ruta, int tamanio, std::string unidad)
{
    std::string directorio = regex_replace(ruta, std::regex("\\w+\\.dsk"), "");
    if (mkdir(directorio.c_str(), 0777) != 0)
    {
        std::cout << "Error al crear el directorio en: " << directorio << std::endl;
        // return;
    }

    std::FILE *fichero = fopen(ruta.c_str(), "w+b");

    if (fichero == NULL)
    {
        std::cout << "Error al crear el disco en: " << ruta << std::endl;
        return;
    }
    char ch = '\0';
    int kilobyte = 1024;

    if (unidad.compare("M") == 0)
        kilobyte = kilobyte * 1024;

    for (int i = 0; i < kilobyte * tamanio; i++)
    {
        // fwrite(&ch, 1, 1, fichero);
        fwrite(&ch, 1, 1, fichero);
    }

    // Obteniendo la hora

    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);

    MBR mbr1;
    mbr1.mbr_tamano = kilobyte;
    mbr1.mbr_dsk_signature = this->numero_random();
    mbr1.mbr_fecha_creacion = end_time;

    this->escribir_mbr(ruta, mbr1);
    std::cout << "Disco creado en: " << ruta << std::endl;
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
        return "Error, el parametro path no viene incluida de manera correcta.";
    case 2:
        return "Error, el parametro size no viene incluído de manera correcta";
    case 3:
        return "Error, el parametro fit no viene incluido de manera correcta";
    case 4:
        return "Error, el parametro unit no viene incluida de manera correcta";
    default:
        return "";
    }
}
#include "../DefinicionClases/mkdisk.h"

void mkdisk::analizador_mkdisk(std::string texto) {
    bool bandera = true;  // size => obligatorio
    bool bandera2 = true; // path => obligatorio
    bool bandera3 = true; // fit => opcional
    bool bandera4 = true; // unit => opcional

    std::string aux = this->tolower_mkdisk(texto); // Variable con el comando en minusculas

    (std::regex_search(aux, std::regex(">path"))) ? bandera2 = this->verificar_ruta_mkdisk(texto) : bandera2 = false;
    (std::regex_search(aux, std::regex(">size"))) ? bandera = this->verificar_tamanio_mkdisk(texto) : bandera = false;
    if (std::regex_search(aux, std::regex(">fit"))) bandera3 = this->verificar_fit_mkdisk(texto);
    if (std::regex_search(aux, std::regex(">unit"))) bandera4 = this->verificar_unidades_mkdisk(texto);
    if (std::regex_search(texto, std::regex("#"))) comentario co(texto);

    if ((bandera == true) && (bandera2 == true) && (bandera3 == true) && (bandera4 == true)) {
        this->crear_disco(this->ruta, this->tamanio, this->unidades);
    } else {
        std::cout << "No se pudo crear el disco." << std::endl;
    }
}

/*  Funciones para verificar    */
bool mkdisk::verificar_ruta_mkdisk(std::string texto) {
    std::smatch ru;
    if (std::regex_search(texto, ru, std::regex(">(P|p)(A|a)(T|t)(H|h)=((/\\w+)+\\.dsk|\"(/(\\w[ ]?)+)+\\.dsk\"|\\w+\\.dsk|\"(\\w[ ]?)+\\.dsk\")")) == true) {
        this->ruta = this->split_text_mkdisk(regex_replace(ru.str(), std::regex("\""), ""), '=', 2);
        return true;
    }
    std::cout << this->errores_mkdisk(1) << std::endl;
    return false;
}

bool mkdisk::verificar_tamanio_mkdisk(std::string texto) {
    std::smatch tm;
    std::string aux = this->tolower_mkdisk(texto);
    if (std::regex_search(aux, tm, std::regex(">size=-?[0-9]+")) == true) {
        int numero = stoi(this->split_text_mkdisk(tm.str(), '=', 2));
        if (numero > 0) {
            this->tamanio = numero;
            return true;
        } else if (numero == 0) {
            std::cout << "El tamaño debe ser mayor que 0." << std::endl;
            return false;
        } else {
            std::cout << "El tamaño no puede ser negativo." << std::endl;
            return false;
        }
    }
    std::cout << this->errores_mkdisk(2) << std::endl;
    return false;
}

bool mkdisk::verificar_fit_mkdisk(std::string texto) {
    std::smatch ft;
    std::string aux = this->tolower_mkdisk(texto);

    if (std::regex_search(aux, ft, std::regex(">fit=(ff|bf|wf)")) == true) {
        if (ft.str().compare("ff") == 0) {
            this->fit = "FF";
        } else if (ft.str().compare("bf") == 0) {
            this->fit = "BF";
        } else {
            this->fit = "WF";
        }
        return true;
    }
    std::cout << this->errores_mkdisk(3) << std::endl;
    return false;
}

bool mkdisk::verificar_unidades_mkdisk(std::string texto) {
    std::smatch un;
    std::string aux = this->tolower_mkdisk(texto);

    if (std::regex_search(aux, un, std::regex(">unit=(m|k)")) == true) {
        if (un.str().compare(">unit=k") == 0) {
            this->unidades = "K";
        } else {
            this->unidades = "M";
        }
        return true;
    }
    std::cout << this->errores_mkdisk(4) << std::endl;
    return false;
}

//
std::string mkdisk::tolower_mkdisk(std::string texto) {
    std::string aux;
    for (int i = 0; i < texto.length(); i++) {
        aux += tolower(texto[i]);
    }
    return aux;
}

std::string mkdisk::split_text_mkdisk(std::string texto, char delimitador, int posicion) {
    std::string aux;
    std::stringstream input_stringstream(texto);
    for (int i = 0; i < posicion; i++) {
        getline(input_stringstream, aux, delimitador);
    }
    return aux;
}

int mkdisk::numero_random() {
    int numeroAleatorio;
    std::srand(time(NULL));

    std::ifstream archivo("./Numeros/numerosAleatorios.eea", std::ios::in);
    if (archivo.fail()) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
    }

    int contador = 0;
    std::string texto;
    while (!archivo.eof()) { 
        getline(archivo, texto); 
        if (texto.compare("") != 0)
            contador++; 
    }
    archivo.seekg(0, std::ios::beg);

    std::ofstream archivo2("./Numeros/numerosAleatorios.eea", std::ios_base::app);
    if (contador == 0) {
        numeroAleatorio = rand() % 100 + 1; 
        archivo2 <<  std::to_string(numeroAleatorio);
    } else {
        int numeros[contador]; //Arreglo para guardar los numeros aleatorios leidos del archivo
        for (int i = 0; i < contador; i++){ //llenando el arreglo con los numeros aleatorios del archivo
            getline(archivo, texto);
            numeros[i] = stoi(texto);
        }
        //Calculando el numero aleatorio 
        do {
            numeroAleatorio = rand() % 100 + 1; 
            for (int i = 0; i < contador; i++) {    //Verificando que el numero aleatorio no se repita
                if (numeroAleatorio == numeros[i]) {
                    numeroAleatorio = 0;
                    break;
                }
            }
        } while (numeroAleatorio == 0); //Si el numero aleatorio es igual a 0, se vuelve a calcular
        archivo2 << "\n" + std::to_string(numeroAleatorio);
    }
    archivo2.close();
    archivo.close();
    return numeroAleatorio;
}

void mkdisk::crear_disco(std::string ruta, int tamanio, std::string unidad) {
    std::string directorio = regex_replace(ruta, std::regex("\\w+\\.dsk"), "");
    this->crear_carpeta(directorio);

    std::FILE *fichero = fopen(ruta.c_str(), "w+b");
    if (fichero == NULL) {
        std::cout << "Error al crear el disco en: " << ruta << " => "<< strerror(errno) << std::endl;
        return;
    }

    char ch = '\0';
    int kilobyte = 1024;

    if (unidad.compare("M") == 0)
        kilobyte = kilobyte * 1024;

    for (int i = 0; i < kilobyte * tamanio; i++) {
        fwrite(&ch, 1, 1, fichero);
    }
    fclose(fichero);

    // Obteniendo la hora
    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);

    MBR mbr1;
    mbr1.mbr_size = kilobyte*tamanio;
    mbr1.mbr_dsk_signature = this->numero_random();
    mbr1.mbr_date_creation = end_time;

    this->escribir_mbr(ruta, mbr1);
    std::cout << "Disco creado en: " << ruta << "." << std::endl;
}

void mkdisk::crear_carpeta(std::string ruta_carpeta) {
    if (ruta_carpeta.compare("") != 0) {
        DIR *dir = opendir(ruta_carpeta.c_str());
        if (dir) {
            closedir(dir);
        } else if (ENOENT == errno) {
            if (mkdir(ruta_carpeta.c_str(), 0777) != 0) {
                std::cout << "Error al crear el directorio en: " << ruta_carpeta <<" => "<<strerror(errno)<< std::endl;
            }
        }
    }
}

void mkdisk::escribir_mbr(std::string ruta, MBR p) {
    std::fstream archivo(ruta, std::ios::out | std::ios::in | std::ios::binary);
    if (archivo.is_open()) {
        archivo.seekp(0);
        archivo.write((char *)&p, sizeof(MBR));
        archivo.close();
    }

    //Insertando el mbr
    // FILE *arch;
    // arch = fopen(ruta.c_str(),"ab");
    // if (arch==NULL) {
    //     std::cout<<"No se pudo escribir el mbr"<<std::endl;
    //     return;
    // }
    // fwrite(&p, sizeof(MBR), 1, arch);
    // fclose(arch);

    // std::cout<<"Ruta: "<<this->ruta<<std::endl;

    // //Leyendo y mostrando el mbr
    FILE *arch2;
    arch2 = fopen(ruta.c_str(), "rb");
    if (arch2 == NULL) {
        std::cout<<"Error al leer el mbr."<<std::endl;
    }
    MBR mbr2; 
    std::cout<<"\nMostrando el mbr: "<<std::endl;
    fread(&mbr2, sizeof(MBR), 1, arch2);
    while (!feof(arch2)) {
        if (mbr2.mbr_size != 0) {
            this->mostrar_mbr(mbr2);
        }
        fread(&mbr2, sizeof(MBR), 1, arch2);
    }
    fclose(arch2);
}

void mkdisk::mostrar_mbr(MBR mbr) {
    std::cout<<"Tamaño: "<<mbr.mbr_size<<std::endl;
    std::cout<<"Dsk: "<<mbr.mbr_dsk_signature<<std::endl;
    std::cout<<"\n"<<std::endl;
}

std::string mkdisk::errores_mkdisk(int tipo_error) {
    switch (tipo_error) {
    case 1: return "Error, el parametro path no viene incluido de manera correcta.";
    case 2: return "Error, el parametro size no viene incluido de manera correcta.";
    case 3: return "Error, el parametro fit no viene incluido de manera correcta.";
    case 4: return "Error, el parametro unit no viene incluido de manera correcta.";
    default: return "";
    }
}
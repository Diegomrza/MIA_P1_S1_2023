#include "../DefinicionClases/rep.h"

void rep::analizador_rep(std::string texto) {
    std::cout<<"Comando en rep: "<<texto<<std::endl;
}

void rep::mostrar(std::string ruta)
{
    
    std::fstream p(ruta, std::ios::out | std::ios::in | std::ios::binary);
    MBR auxP;

    if (p.is_open())
    {
        p.read((char *)&auxP, sizeof(auxP));
        while (!p.eof())
        {
            if (auxP.mbr_size != 0)
            {
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


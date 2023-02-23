#include "../DefinicionClases/rep.h"

void rep::mostrar(std::string ruta)
{
    
    std::fstream p(ruta, std::ios::out | std::ios::in | std::ios::binary);
    MBR auxP;

    if (p.is_open())
    {
        p.read((char *)&auxP, sizeof(auxP));
        while (!p.eof())
        {
            if (auxP.mbr_tamano != 0)
            {
                std::cout << "Tamanio: " << auxP.mbr_tamano;
                std::cout << "   Numero: " << auxP.mbr_dsk_signature;
                std::cout << "   Fecha: " << std::ctime(&auxP.mbr_fecha_creacion);
                std::cout << std::endl;
            }

            p.read((char *)&auxP, sizeof(auxP));
        }

        p.close();
    }
}


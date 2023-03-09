#ifndef STRUCTMBR_H
#define STRUCTMBR_H

#include "./structParticion.h"

// Struct MBR
struct MBR
{
public:
    int mbr_size = 0; //Tamaño total del disco
    time_t mbr_date_creation; //Fecha de creación del disco
    int mbr_dsk_signature; //Número aleatorio único para identificar cada disco

    char mbr_fit = 'F'; //F, B, W

    structParticion mbr_partition1;
    structParticion mbr_partition2;
    structParticion mbr_partition3;
    structParticion mbr_partition4;
};

#endif
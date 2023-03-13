#ifndef STRUCTEBR_H
#define STRUCTEBR_H

struct EBR
{
    char part_status = '0';  // Estado de la particion (0 = inactiva, 1 = activa)
    char part_fit = '0';     // Tipo de ajuste de la particion (F, W,B)
    int part_start = 0;      // Byte de inicio de la particion
    int part_s = 0;          // Tamaño de la particion
    int part_next = -1;       // Byte de inicio de la siguiente particion
    char part_name[16] = ""; // Nombre de la particion
};

#endif
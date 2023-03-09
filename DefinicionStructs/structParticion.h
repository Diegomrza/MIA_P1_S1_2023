#ifndef STRUCTPARTICION_H
#define STRUCTPARTICION_H

struct structParticion
{
    char part_status = '0';  // Activa o no activa
    char part_type = '0';    // Primaria = P, Extendida = E
    char part_fit = '0';     // Ajuste => F(First), B(Best), W(Worst)
    int part_start = 0;      // Indica en que byte inicia la partición
    int part_s = 0;          // Tamaño en bytes de la partición
    char part_name[16] = ""; // Nombre de la partición
};

#endif
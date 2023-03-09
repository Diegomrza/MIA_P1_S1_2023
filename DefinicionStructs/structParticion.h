#ifndef STRUCTPARTICION_H
#define STRUCTPARTICION_H

struct structParticion
{
    char status = '0';  // 0, 1
    char type[1] = "";  // Primaria = P, Extendida = E
    char fit[2] = "";   // Ajuste => F(First), B(Best), W(Worst)
    int size = 0;       // Tamaño en bytes de la partición
    char name[25] = ""; // Nombre de la partición
    int start = 0;      // Indica en que byte inicia la partición
};

#endif
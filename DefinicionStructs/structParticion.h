#ifndef STRUCTPARTICION_H
#define STRUCTPARTICION_H

struct structParticion
{
    char status = '0';
    int tamanio = 0;
    char ruta[25] = "";
    char nombre[25] = "";
    char tipo[1] = "";
    char ajuste[2] = "";
    char unidades[1] = "";
};

#endif
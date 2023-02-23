#ifndef STRUCTP_H
#define STRUCTP_H

// Struct profesor
struct Profesor
{
public:
    int Tipo = 1;
    int Id_profesor = 0;
    char CUI[15] = "";
    char Nombre[25] = "";
    char Curso[25] = "";
};

#endif
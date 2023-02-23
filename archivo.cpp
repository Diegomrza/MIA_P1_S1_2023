#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <iostream>
#include <fstream>
#include <cstring> //Para usar memcpy

#include "./DefinicionStructs/structP.h"
#include "./DefinicionStructs/structE.h"

using namespace std;

class archivo
{
private:
    int len_p; // Tamaño de registros profesor   ---> len = length ; p = profesor    <---
    int len_e; // Tamaño de registros estudiante ---> len = length ; e = estudiante  <---

public:
    archivo();
    ~archivo();

    /*
    Crea el archivo
    */
    void crear_archivo();

    /*
    Toma de datos
    */
    void pedir_datos_profesor();
    void pedir_datos_estudiante();

    /*
    Escritura en archivo binario
    */
    void escribir_profesor(Profesor);
    void escribir_estudiante(Estudiante);

    /*
    Muestra datos del archivo binario
    */
    void ver_registros();
    void mostrar_p();
    void mostrar_e();

    /*
    
    */
   
};

//  Constructor  //
archivo::archivo(/* args */)
{
    this->len_p = 0;
    this->len_e = 0;
    this->crear_archivo();
}

//  Destructor   //
archivo::~archivo()
{
}

//  Métodos de clase archivo    //
void archivo::crear_archivo()
{
    fstream archivo;
    archivo.open("archivo.mia");
    if (!archivo)
    {
        ofstream fichero("archivo.mia");
    }
    archivo.close();
}

void archivo::escribir_profesor(Profesor p)
{
    fstream archivo("archivo.mia", ios::out | ios::in | ios::binary);
    if (archivo.is_open())
    {
        archivo.seekp((p.Id_profesor - 1) * sizeof(Profesor));
        archivo.write((char *)&p, sizeof(Profesor));
        archivo.close();
    }
}

void archivo::escribir_estudiante(Estudiante es)
{
    fstream archivo("archivo.mia", ios::out | ios::in | ios::binary);
    if (archivo.is_open())
    {
        archivo.seekp((es.Id_estudiante - 1) * sizeof(Estudiante));
        archivo.write((char *)&es, sizeof(Estudiante));
        archivo.close();
    }
}

void archivo::pedir_datos_profesor()
{
    int id;
    char cui[15];
    char nombre[25];
    char curso[25];

    cout << "Ingrese el id: " << endl;
    cin >> id;
    cout << "Ingrese el cui: " << endl;
    cin >> cui;
    cout << "Ingrese el nombre: " << endl;
    cin >> nombre;
    cout << "Ingrese el curso: " << endl;
    cin >> curso;

    Profesor nuevo;
    nuevo.Id_profesor = id;
    memcpy(nuevo.CUI, cui, 15);
    memcpy(nuevo.Nombre, nombre, 25);
    memcpy(nuevo.Curso, curso, 25);
    this->escribir_profesor(nuevo);
}

void archivo::pedir_datos_estudiante()
{
    int id;
    char cui[15];
    char nombre[25];
    char carnet[25];

    cout << "Ingrese el id: " << endl;
    cin >> id;
    cout << "Ingrese el cui: " << endl;
    cin >> cui;
    cout << "Ingrese el nombre:" << endl;
    cin >> nombre;
    cout << "Ingrese el carnet: " << endl;
    cin >> carnet;

    Estudiante nuevo;
    nuevo.Id_estudiante = id;
    memcpy(nuevo.CUI, cui, 15);
    memcpy(nuevo.Nombre, nombre, 25);
    memcpy(nuevo.Carnet, carnet, 25);

    this->escribir_estudiante(nuevo);
}

void archivo::ver_registros()
{
    cout << "Profesores: " << endl;

    fstream p("archivo.mia", ios::out | ios::in | ios::binary);
    Profesor auxP;

    if (p.is_open())
    {
        p.read((char *)&auxP, sizeof(Profesor));

        while (!p.eof())
        {
            if (auxP.Tipo == 1)
            {
                cout << "ID: " << auxP.Id_profesor;
                cout << "   CUI: " << auxP.CUI;
                cout << "   Nombre: " << auxP.Nombre;
                cout << "   Curso: " << auxP.Curso;
                cout << endl;
            }
            p.read((char *)&auxP, sizeof(Profesor));
        }
        p.close();
    }

    cout << "Estudiantes: " << endl;
    fstream e("archivo.mia", ios::out | ios::in | ios::binary);
    Estudiante auxE;

    if (e.is_open())
    {
        e.read((char *)&auxE, sizeof(Estudiante));
        while (!e.eof())
        {
            if (auxE.Tipo == 2)
            {
                cout << "Id: " << auxE.Id_estudiante;
                cout << "   CUI: " << auxE.CUI;
                cout << "   Nombre: " << auxE.Nombre;
                cout << "   Carnet: " << auxE.Carnet;
                cout << endl;
            }
            e.read((char *)&auxE, sizeof(Estudiante));
        }
        e.close();
    }
}

#endif
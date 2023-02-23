#ifndef MENU_H
#define MENU_H

#include <string>

class menu
{
private:
    void iniciar_menu();
    void mostrar_mensajes();
    int registrar_opcion(int);
    void ejecutar_opcion(int);
    void error_opciones(int);
public:
    menu();
    ~menu();
};

menu::menu()
{
    this->iniciar_menu();
}

menu::~menu()
{
}

#endif
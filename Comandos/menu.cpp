#include "../DefinicionClases/menu.h"
#include <iostream>
#include <string>

void menu::iniciar_menu()
{
    int opcion = 0;
    while (opcion == 0)
    {
        this->mostrar_mensajes();
        opcion = this->registrar_opcion(opcion);
    }
    this->ejecutar_opcion(opcion);
}

void menu::mostrar_mensajes()
{
    std::cout << "1. Opción 1" << std::endl;
    std::cout << "2. Opción 2" << std::endl;
    std::cout << "3. Opción 3" << std::endl;
    std::cout << "4. Salir" << std::endl;
    std::cout << "Diego Abraham Robles Meza" << std::endl;
    std::cout << "201901429" << std::endl;
}

int menu::registrar_opcion(int opcion)
{
    std::cout << "Ingrese una opción: " << std::endl;
    std::string op;
    std::cin >> op;

    try
    {
        opcion = stoi(op);
    }
    catch (const std::exception &e)
    {
        this->error_opciones(-1);
        return 0;
    }

    if (opcion <= 0 || opcion > 4)
    {
        this->error_opciones(opcion);
        return 0;
    }
    else
    {
        return opcion;
    }
}

void menu::ejecutar_opcion(int opcion)
{
    if (opcion == 1)
    {
        std::cout << "Ingresó la opción 1" << std::endl;
    }
    else if (opcion == 2)
    {
        std::cout << "Ingresó la opción 2" << std::endl;
    }
    else if (opcion == 3)
    {
        std::cout << "Ingresó la opción 3" << std::endl;
    }
    else if (opcion == 4)
    {
        std::cout << "Saliendo de la aplicación..." << std::endl;
        exit(1);
    }
}

void menu::error_opciones(int opcion)
{

    if (opcion == -1)
    {
        std::cout << "Ingrese solamente números." << std::endl;
    }
    else if (opcion < 0)
    {
        std::cout << "Ingrese solamente numeros positivos." << std::endl;
    }
    else if (opcion > 3)
    {
        std::cout << "Solamente existen 3 opciones." << std::endl;
    }
    else if (opcion == 0)
    {
        std::cout << "Cero no es una opción." << std::endl;
    }
}

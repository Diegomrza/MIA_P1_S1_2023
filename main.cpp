//#include "archivo.cpp"

#include <regex>
#include <iostream>

#include "./Comandos/execute.cpp"

// int opciones(int op, archivo arch)
// {
//     if (op == 1)
//     {
//         arch.pedir_datos_profesor();
//     }
//     else if (op == 2)
//     {
//         arch.pedir_datos_estudiante();
//     }
//     else if (op == 3)
//     {
//         arch.ver_registros();
//     }
//     else if (op == 4)
//     {
//         exit(1);
//     }
//     else
//     {
//         std::cout << "Opcion incorrecta." << std::endl;
//     }
//     return 0;
// }

// void menu()
// {
//     archivo arch;
//     int opcion = 0;
//     while (opcion == 0)
//     {
//         std::cout << "*****************************" << std::endl;
//         std::cout << "* Diego Abraham Robles Meza *" << std::endl;
//         std::cout << "*         201901429         *" << std::endl;
//         std::cout << "*****************************" << std::endl;
//         std::cout << "1. Registro de Profesor" << std::endl;
//         std::cout << "2. Registro de Estudiante" << std::endl;
//         std::cout << "3. Ver Registros" << std::endl;
//         std::cout << "4. Salir" << std::endl;
//         std::cout << "Ingresa una opción: ";
//         std::cin >> opcion;
//         std::cout << std::endl << std::endl;
//         opcion = opciones(opcion, arch);
//     }
// }

int main()
{
    std::cout << "Diego Abraham Robles Meza" << std::endl;
    std::cout << "201901429" << std::endl;

    std::cout << "Ingrese un comando:" << std::endl;
    std::string comando;
    getline(std::cin, comando);

    std::cout << "::::::Este es el comando:::::" << std::endl;
    std::cout << comando << std::endl;

    execute nuevo(comando);

    return 0;
}

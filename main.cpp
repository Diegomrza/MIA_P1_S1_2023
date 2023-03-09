#include <iostream>
#include "./Comandos/execute.cpp"

int main()
{
    std::cout << "Diego Abraham Robles Meza\n201901429\nIngrese un comando:" << std::endl;
    std::boolalpha;
    std::string comando = "ExEcUtE >PaTh=prueba.eea";
    //getline(std::cin, comando);
    
    char nombre1[25];
    strcpy(nombre1, "Particion1");

    char nombre2[] = "Particion1";
    std::cout<<(strcmp(nombre1, nombre2))<<std::endl;

    //execute nuevo(comando);
    return 0;
}

#include <iostream>

#include "./Comandos/execute.cpp"

int main()
{
    std::cout << "Diego Abraham Robles Meza\n201901429\nIngrese un comando:" << std::endl;
    std::string comando;
    getline(std::cin, comando);
    std::cout<<std::endl;
    execute nuevo(comando);
    //      execute >path=prueba.eea
    return 0;
}

#include <iostream>

#include "./Comandos/execute.cpp"

int main()
{
    std::cout << "Diego Abraham Robles Meza" << std::endl;
    std::cout << "201901429" << std::endl;

    std::cout << "Ingrese un comando:" << std::endl;
    std::string comando;
    getline(std::cin, comando);
    std::cout<<std::endl;
    execute nuevo(comando);

    return 0;
}

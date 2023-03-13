#include <iostream>
#include "./Comandos/execute.cpp"
using namespace std;

int main()
{
    std::cout << "Diego Abraham Robles Meza\n201901429\nIngrese un comando:\n" << std::endl;
    std::string comando = "ExEcUtE >PaTh=prueba.eea #Comentario execute";
    //getline(std::cin, comando);

    execute nuevo(comando);

    return 0;
}

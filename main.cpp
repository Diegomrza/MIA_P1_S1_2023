#include <iostream>
#include "./Comandos/execute.cpp"
#include "./Grafos/grafo.cpp"
#include "./DefinicionStructs/structMBR.h"
#include "./DefinicionStructs/structParticion.h"

using namespace std;

int main()
{
    std::cout << "Diego Abraham Robles Meza\n201901429\nIngrese un comando:\n" << std::endl;
    std::string comando = "ExEcUtE >PaTh=prueba.eea #Comentario execute";
    //getline(std::cin, comando);

    execute nuevo(comando);
    return 0;
}

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

    // std::map<int, std::string> mapa;

    // EBR ebr1 = {'0','F', ebr1.part_s, 150, -1, "partition1"};
    // EBR ebr2 = {'0','F', ebr2.part_s, 25000, -1, "partition2"};
    // EBR ebr3 = {'0','F', ebr3.part_s, 5000, -1, "partition3"};
    // EBR ebr4 = {'0','F', ebr4.part_s, 30, -1, "partition4"};
    // EBR ebr5 = {'0','F', ebr5.part_s, 10, -1, "partition5"};
    // EBR ebr6 = {'0','F', ebr6.part_s, 15000, -1, "partition6"};
    // EBR ebr7 = {'0','F', ebr7.part_s, 100, -1, "partition7"};
    // EBR ebr8 = {'0','F', ebr8.part_s, 20, -1, "partition8"};

    // mapa.insert(std::pair<int, std::string>(ebr2.part_start-ebr1.part_start, "ebr2_ebr1"));
    // mapa.insert(std::pair<int, std::string>(ebr3.part_start-ebr2.part_start, "ebr3_ebr2"));
    // mapa.insert(std::pair<int, std::string>(ebr4.part_start-ebr3.part_start, "ebr4_ebr3"));
    // mapa.insert(std::pair<int, std::string>(ebr5.part_start-ebr4.part_start, "ebr5_ebr4"));
    // mapa.insert(std::pair<int, std::string>(ebr6.part_start-ebr5.part_start, "ebr6_ebr5"));
    // mapa.insert(std::pair<int, std::string>(ebr7.part_start-ebr6.part_start, "ebr7_ebr6"));
    // mapa.insert(std::pair<int, std::string>(ebr8.part_start-ebr7.part_start, "ebr8_ebr7"));
    // mapa.insert(std::pair<int, std::string>(ebr1.part_start-ebr8.part_start, "ebr1_ebr8"));

    // //std::sort(mapa.begin(), mapa.end(), std::greater<std::pair<int, EBR>>());

    // // Imprimir los elementos del map ordenados de forma descendente
    // for (auto it = mapa.begin(); it != mapa.end(); ++it) {
    //     std::cout << it->first << " => " << it->second << '\n';
    // }
    
    
    // MBR mbr;
    // mbr.mbr_size = 5120; //5242880
    // mbr.mbr_dsk_signature = 10;
    // mbr.mbr_fit = 'F';
    
    // structParticion part1 = {'0','P', 'F', 150, 500, "partition1"};
    // structParticion part2 = {'0','P', 'F', 25000, 500, "partition2"};
    // structParticion part3 = {'0','P', 'W', 5000, 500, "partition3"};
    // structParticion part4 = {'0','P', 'B', 30, 500, "partition4"};

    // mbr.mbr_partition1 = part1;
    // //mbr.mbr_partition2 = part2;
    // mbr.mbr_partition3 = part3;
    // //mbr.mbr_partition4 = part4;

    // FILE *arch;
    // arch = fopen("Disco1.dsk", "rb");
    // if (arch == NULL) {
    //     std::cout << "Error al leer el mbr." << std::endl;
    //     exit(1);
    // }
    // MBR mbr;
    
    // fread(&mbr, sizeof(MBR), 1, arch);
    // while (!feof(arch)) {
    //     if (mbr.mbr_size != 0) {
    //         break;
    //     }
    //     fread(&mbr, sizeof(MBR), 1, arch);
    // }
    // fclose(arch);

    // Grafo g("Grafo1","png", mbr);

    return 0;
}

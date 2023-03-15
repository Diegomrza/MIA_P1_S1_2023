#include <iostream>
#include "./Comandos/execute.cpp"
using namespace std;

int main()
{
    std::cout << "Diego Abraham Robles Meza\n201901429\nIngrese un comando:\n" << std::endl;
    std::string comando = "ExEcUtE >PaTh=prueba.eea #Comentario execute";
    //getline(std::cin, comando);

    //execute nuevo(comando);


    EBR arreglo[24];
    
    std::fstream archivo("Disco1.dsk", std::ios::out | std::ios::in | std::ios::binary);
    if (archivo.is_open()) {
        archivo.seekp(2*sizeof(EBR));
        EBR ebr = { '1', 'F', 0, 0, -1, "EBR" };
        //archivo.write((char *)&ebr, sizeof(EBR));
        for (int i = 0; i < 5; i++) {
            ebr = { '1', 'F', 0, 0, -1, "CCCs"};
            archivo.write((char *)&ebr, sizeof(EBR));
        }
        
        archivo.close();
    }

    std::fstream archivo2("Disco1.dsk", std::ios::out | std::ios::in | std::ios::binary);
    if (archivo2.is_open()) {
        EBR ebr;
        archivo2.seekp(0);
        int contador = 0;
        archivo2.read((char *)&ebr, sizeof(EBR));
        while (!archivo2.eof()) {
            std::cout<<"\nEBR: "<<std::endl;
            std::cout<<"Nombre: "<<ebr.part_name<<std::endl;
            if (strcmp(ebr.part_name, "") != 0) {
                arreglo[contador] = ebr;
                contador++;
            }
            archivo2.read((char *)&ebr, sizeof(EBR));
        }
        
        
    }
    return 0;
}

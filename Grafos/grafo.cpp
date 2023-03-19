#include "grafo.h"

void Grafo::administrador_grafos(std::string tipo, std::string ruta, std::string formato, std::string nombre_archivo) {
    if (tipo=="MBR") {
        this->reporte_mbr(ruta, formato, nombre_archivo);
    } else if (tipo=="DISK") {
        this->reporte_disk(ruta, formato, nombre_archivo);
    } else if (tipo=="INODE") {
        this->reporte_inode(ruta, formato, nombre_archivo);
    } else if (tipo=="JOURNALING") {
        this->reporte_journaling(ruta, formato, nombre_archivo);
    } else if (tipo=="BLOCK") {
        this->reporte_block(ruta, formato, nombre_archivo);
    } else if (tipo=="BM_INODE") {
        this->reporte_bm_inode(ruta, formato, nombre_archivo);
    } else if (tipo=="BM_BLOCK") {
        this->reporte_bm_block(ruta, formato, nombre_archivo);
    } else if (tipo=="TREE") {
        this->reporte_tree(ruta, formato, nombre_archivo);
    } else if (tipo=="SB") {
        this->reporte_sb(ruta, formato, nombre_archivo);
    } else if (tipo=="FILE") {
        this->reporte_file(ruta, formato, nombre_archivo);
    } else if (tipo=="LS") {
        this->reporte_ls(ruta, formato, nombre_archivo);
    }
}

std::string Grafo::reporte_mbr(std::string ruta, std::string formato, std::string nombre_archivo) {
    FILE *archivo;
    archivo = fopen(ruta.c_str(), "rb");
    if (archivo == NULL) {
        std::cout << "Error: no se pudo abrir el archivo." << std::endl;
        return "";
    }
    MBR mbr;
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo);
    fclose(archivo);

    return "";
}

std::string Grafo::reporte_disk(std::string ruta, std::string formato, std::string nombre_archivo) {
    FILE *archivo;
    archivo = fopen(ruta.c_str(), "rb");
    if (archivo == NULL) {
        std::cout << "Error: no se pudo abrir el archivo." << std::endl;
        return "";
    }
    MBR mbr;
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo);
    fclose(archivo);

    int contador_libres = 1;    

    std::string grafo = "digraph MyGraph {\n";
    grafo += "node [shape=plaintext];\n";
    grafo += "tabla [label=<<table border=\"1\" cellborder=\"1 \" cellspacing=\"2\">\n";
   
    grafo += "<tr>\n";

    grafo += "<td>\n";
    grafo += "MBR";
    grafo += "</td>\n";

    grafo += "<td>";
    if (mbr.mbr_partition1.part_s==0) {
        grafo += "Libre \n";
        grafo += std::to_string(contador_libres);
        contador_libres++;
    } else {
        grafo += mbr.mbr_partition1.part_name;
        grafo += " \n";
        grafo += std::to_string(mbr.mbr_partition1.part_s);
        grafo += " \n";
        grafo += "bytes\n";
    }
    grafo += "</td>\n";
    grafo += "<td>";
    if (mbr.mbr_partition2.part_s==0) {
        grafo += "Libre \n";
        grafo += std::to_string(contador_libres);
        contador_libres++;
    } else {
        grafo += mbr.mbr_partition2.part_name;
        grafo += " \n";
        grafo += std::to_string(mbr.mbr_partition2.part_s);
        grafo += " \n";
        grafo += "bytes\n";
    }
    grafo += "</td>\n";
    grafo += "<td>";
    if (mbr.mbr_partition3.part_s==0) {
        grafo += "Libre \n";
        grafo += std::to_string(contador_libres);
        contador_libres++;
    } else {
        grafo += mbr.mbr_partition3.part_name;
        grafo += " \n";
        grafo += std::to_string(mbr.mbr_partition3.part_s);
        grafo += " \n";
        grafo += "bytes\n";
    }
    grafo += "</td>\n";
    grafo += "<td>";
    if (mbr.mbr_partition4.part_s==0) {
        grafo += "Libre \n";
        grafo += std::to_string(contador_libres);
        contador_libres++;
    } else {
        grafo += mbr.mbr_partition4.part_name;
        grafo += " \n";
        grafo += std::to_string(mbr.mbr_partition4.part_s);
        grafo += " \n";
        grafo += "bytes\n";
    }
    grafo += "</td>\n";
    grafo += "</tr>\n";

    grafo += "</table>>];\n}";
    return grafo;
}

std::string Grafo::reporte_inode(std::string ruta, std::string formato, std::string nombre_archivo) {
    return "";
}

std::string Grafo::reporte_journaling(std::string ruta, std::string formato, std::string nombre_archivo) {
    return "";
}

std::string Grafo::reporte_block(std::string ruta, std::string formato, std::string nombre_archivo) {
    return "";
}

std::string Grafo::reporte_bm_inode(std::string ruta, std::string formato, std::string nombre_archivo) {
    return "";
}

std::string Grafo::reporte_bm_block(std::string ruta, std::string formato, std::string nombre_archivo) {
    return "";
}

std::string Grafo::reporte_tree(std::string ruta, std::string formato, std::string nombre_archivo) {
    return "";
}

std::string Grafo::reporte_sb(std::string ruta, std::string formato, std::string nombre_archivo) {
    return "";
}

std::string Grafo::reporte_file(std::string ruta, std::string formato, std::string nombre_archivo) {
    return "";
}

std::string Grafo::reporte_ls(std::string ruta, std::string formato, std::string nombre_archivo) {
    return "";
}

std::string Grafo::generar_archivo_dot(std::string nombre_archivo, std::string ruta, std::string codigo_graphviz) {
    std::string filename(ruta + nombre_archivo + ".dot");
    std::fstream file_out;

    file_out.open(filename, std::ios_base::out);
    if (!file_out.is_open())
    {
        return "Error";
    }
    file_out << codigo_graphviz << std::endl;
    //std::cout << "La escritura fue un exito" << std::endl;
    
    return filename;
}

std::string Grafo::generar_codigo_graphviz(MBR mbr) {

    int contador_libres = 1;    

    std::string grafo = "digraph MyGraph {\n";
    grafo += "node [shape=plaintext];\n";
    grafo += "tabla [label=<<table border=\"1\" cellborder=\"1 \" cellspacing=\"2\">\n";
   
    grafo += "<tr>\n";

    grafo += "<td>\n";
    grafo += "MBR";
    grafo += "</td>\n";

    grafo += "<td>";
    if (mbr.mbr_partition1.part_s==0) {
        grafo += "Libre \n";
        grafo += std::to_string(contador_libres);
        contador_libres++;
    } else {
        grafo += mbr.mbr_partition1.part_name;
        grafo += " \n";
        grafo += std::to_string(mbr.mbr_partition1.part_s);
        grafo += " \n";
        grafo += "bytes\n";
    }
    grafo += "</td>\n";
    grafo += "<td>";
    if (mbr.mbr_partition2.part_s==0) {
        grafo += "Libre \n";
        grafo += std::to_string(contador_libres);
        contador_libres++;
    } else {
        grafo += mbr.mbr_partition2.part_name;
        grafo += " \n";
        grafo += std::to_string(mbr.mbr_partition2.part_s);
        grafo += " \n";
        grafo += "bytes\n";
    }
    grafo += "</td>\n";
    grafo += "<td>";
    if (mbr.mbr_partition3.part_s==0) {
        grafo += "Libre \n";
        grafo += std::to_string(contador_libres);
        contador_libres++;
    } else {
        grafo += mbr.mbr_partition3.part_name;
        grafo += " \n";
        grafo += std::to_string(mbr.mbr_partition3.part_s);
        grafo += " \n";
        grafo += "bytes\n";
    }
    grafo += "</td>\n";
    grafo += "<td>";
    if (mbr.mbr_partition4.part_s==0) {
        grafo += "Libre \n";
        grafo += std::to_string(contador_libres);
        contador_libres++;
    } else {
        grafo += mbr.mbr_partition4.part_name;
        grafo += " \n";
        grafo += std::to_string(mbr.mbr_partition4.part_s);
        grafo += " \n";
        grafo += "bytes\n";
    }
    grafo += "</td>\n";
    grafo += "</tr>\n";

    grafo += "</table>>];\n}";
    return grafo;
}

void Grafo::generar_grafo(std::string ruta, std::string formato, MBR mbr) {
    std::string codigo = this->generar_codigo_graphviz(mbr);
    if (codigo.compare("Error")==0) {
        std::cout << "Error al generar el codigo graphviz" << '\n';
        return;
    }
    if (this->generar_archivo_dot(ruta, "", codigo).compare("Error") == 0) {
        std::cout << "Error al abrir el archivo: " << ruta << '\n';
        return;
    }
    std::string cmd = "dot -T"+formato + " " + ruta+".dot" + " -o " + ruta + "." + formato;
    system(cmd.c_str());
    //std::string nombre = ruta + "." + formato;
    //system(ruta.c_str());
}

void Grafo::generar(std::string ruta, std::string formato, MBR mbr) {
    std::string codigo = this->generar_codigo_graphviz(mbr);
    if (codigo.compare("Error")==0) {
        std::cout << "Error al generar el codigo graphviz" << '\n';
        return;
    }
    if (this->generar_archivo_dot(ruta, "", codigo).compare("Error") == 0) {
        std::cout << "Error al abrir el archivo: " << ruta << '\n';
        return;
    }
    std::string cmd = "dot -T"+formato + " " + ruta +".dot" + " -o " + ruta + "." + formato;
    system(cmd.c_str());
}

MBR Grafo::obtener_mbr(std::string ruta) {
    FILE *archivo = fopen(ruta.c_str(), "rb");
    if (archivo == NULL) {
        std::cout << "Error: no se pudo abrir el archivo." << std::endl;
        return MBR();
    }
    MBR mbr;
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo);
    fclose(archivo);
    return mbr;
}
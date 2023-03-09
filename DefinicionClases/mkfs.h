#ifndef MKFS_H
#define MKFS_H

#include <string>
#include <regex>

class mkfs
{
private:
    std::string id;   // obligatorio
    std::string type; // opcional
    std::string fs;   // opcional => 2fs ó 3fs
    void analizador_mkfs(std::string);
    bool verificar_id_mkfs(std::string);
    bool verificar_tipo_mkfs(std::string);
    bool verificar_fs_mkfs(std::string);

    std::string tolower_mkfs(std::string);
    std::string split_mkfs(std::string, char, int);

public:
    mkfs();
    ~mkfs();
};

mkfs::mkfs()
{
    this->id = "";
    this->fs = "2fs";
    this->type = "Full";
}

mkfs::~mkfs()
{
}

#endif
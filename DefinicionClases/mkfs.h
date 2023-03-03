#ifndef MKFS_H
#define MKFS_H

#include <string>

class mkfs
{
private:
    std::string id;   // obligatorio
    std::string type; // opcional
    std::string fs;   // opcional => 2fs ó 3fs
    

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
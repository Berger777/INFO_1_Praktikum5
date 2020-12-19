#ifndef PRAKTIKUM_5_MAIN_H
#define PRAKTIKUM_5_MAIN_H
#include "string.h"

#endif //PRAKTIKUM_5_MAIN_H

#define standardBufferSize 128


struct vokabel{
    int id;
    char frage[standardBufferSize];
    char antwort[standardBufferSize];
    struct vokabel* prev;
    struct vokabel* next;
};
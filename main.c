#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void vokabelListeAusgeben(struct vokabel *erstesElement);

void vokabelnEinlesen(struct vokabel *anfang);

void vokabelnSpeichern(struct vokabel *anfang, char name[standardBufferSize]);

void vokabelZufuegen(struct vokabel *erstesElement, char vokabel[standardBufferSize]);

struct vokabel *vokabelLoeschen(char vokabel[standardBufferSize], struct vokabel *listeFirst);

void vokabelAbfragen(struct vokabel *liste);

void readInput(char *var);


int main() {
    printf("Praktikum 5:\n");
    printf("----> 	Bitte Befehl eingeben	 <----\n");
    char command[standardBufferSize];
    struct vokabel *anfang = malloc(sizeof(struct vokabel));
    anfang->id = -1;
    readInput(command);

    while (strcmp(command, "quit") != 0) {
        if (strcmp(command, "read") == 0) {
            vokabelnEinlesen(anfang);
        } else if (strcmp(command, "use") == 0) {
            vokabelAbfragen(anfang);
        } else if (strcmp(command, "save") == 0) {
            char dateiname[standardBufferSize];
            printf("----> \tVokabeldateinamen angeben:\t <----\n");
            readInput(dateiname);
            vokabelnSpeichern(anfang, dateiname);
        } else if (strcmp(command, "add") == 0) {
            char vokabel[standardBufferSize];
            printf("----> \tVokabel eingeben:\t <----\n");
            readInput(vokabel);
            vokabelZufuegen(anfang, vokabel);
        } else if (strcmp(command, "del") == 0) {
            char vokabel[standardBufferSize];
            printf("----> \tVokabel eingeben:\t <----\n");
            readInput(vokabel);
            anfang = vokabelLoeschen(vokabel, anfang);
        }else if(strcmp(command, "view") == 0){
            vokabelListeAusgeben(anfang);
        }else{
            printf("----> \tUnbekannter Befehl\t <----\n");
        }
        printf("----> 	Bitte Befehl eingeben	 <----\n");
        readInput(command);
    }
    printf("----> \tProgramm beendet\t <----");
    return 0;
}

void readInput(char *var) {
    fgets(var, standardBufferSize, stdin);
    strtok(var, "\n");
}

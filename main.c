#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void vokabelListeAusgeben(struct vokabel* erstesElement);
void vokabelnEinlesen(struct vokabel* anfang);
void vokabelnSpeichern();
void vokabelnZufuegen();
void vokabelnLoeschen();

void readCommand(char *command);


int main() {
    printf("Praktikum 5:\n");
    printf("----> 	Bitte Befehl eingeben	 <----\n");
    char command[standardBufferSize];
    struct vokabel *anfang = malloc(sizeof(struct vokabel));
    anfang->id = -1;
    readCommand(command);

    while (strcmp(command, "quit") != 0) {
        if (strcmp(command, "read") == 0) {
            vokabelnEinlesen(anfang);
        } else if (strcmp(command, "save") == 0) {
            vokabelnSpeichern();
        } else if (strcmp(command, "add") == 0) {
            //vokabelnZufuegen();
        } else if (strcmp(command, "del") == 0) {
            //vokabelnLoeschen();
        }else if(strcmp(command,"view")==0){
            vokabelListeAusgeben(anfang);
        }else{
            printf("----> \tUnbekannter Befehl\t <----\n");
        }
        printf("----> 	Bitte Befehl eingeben	 <----\n");
        readCommand(command);
    }
    printf("----> \tProgramm beendet\t <----");
    return 0;
}

void readCommand(char *command) {
    fgets(command, standardBufferSize, stdin);
    strtok(command, "\n");
}

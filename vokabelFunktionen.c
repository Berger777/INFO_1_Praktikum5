#include <stdio.h>
#include <stdlib.h>
#include "main.h"

struct vokabel* neueVokabelStruct(int id, char frage[standardBufferSize], char antwort[standardBufferSize],struct vokabel* prev);
void vokabelInListeZufuegen(char frage[standardBufferSize], char antwort[standardBufferSize], int id, struct vokabel* anfang);
void error(char errorDesc[standardBufferSize]);
char** vokabelEinlesenDecode(char vokabeln[standardBufferSize]);

/**
 * Liest aus einer Datei Vokabeln ein und speichert diese in der Liste
 * @param first - erstes Element der Liste
 */
void vokabelnEinlesen(struct vokabel *first) {
    char name[standardBufferSize];
    printf("----> \tVokabeldateinamen angeben:\t <----\n");
    fgets(name, standardBufferSize, stdin);
    strtok(name, "\n");
    FILE *datei = fopen(name, "r");
    if (datei == NULL) {
        error("Fehler beim Lesen der Datei!\n");
    } else {
        char vokabeln[standardBufferSize][standardBufferSize];
        int i = 0;
        while (fgets(vokabeln[i++], standardBufferSize, datei) != NULL) {
            char** retVal = vokabelEinlesenDecode(vokabeln[i-1]);
            char* frage = retVal[0];
            char* antwort = retVal[1];
            vokabelInListeZufuegen(frage,antwort, i-1, first);
            free(antwort);
            free(frage);
            free(retVal);
        }
        printf("----> \tVokabeln eingelesen!\t <----\n");
    }
}

/**
 * Decoded den eingelesenen String
 * @param vokabeln - Encodeder String
 * @return - char** mit [0] String frage und [1] String antwort
 */
char** vokabelEinlesenDecode(char vokabeln[standardBufferSize]){
    int delimterIndex = 0;
    char frage[standardBufferSize] = "\0";
    char antwort[standardBufferSize] = "\0";
    //char retVal[2][standardBufferSize];
    char** retVal = malloc(2 * sizeof (char*));
    retVal[0] = malloc(sizeof (char[standardBufferSize]));
    retVal[1] = malloc(sizeof (char[standardBufferSize]));

    //Frage einlesen
    for (int v = 0; v < standardBufferSize; ++v) {
        if (vokabeln[v]==';'){
            delimterIndex = v;
            break;
        }else{
            frage[v] = vokabeln[v];
        }
    }
    strcpy(retVal[0],frage);
    //printf("Speichere Frage:%s\n",frage);

    //Antwort einlesen
    int arrCnt = 0;
    for (int j = delimterIndex+1; j < standardBufferSize; ++j) {
        if (vokabeln[j]=='\n'){
            break;
        }else{
            antwort[arrCnt++] = vokabeln[j];
        }
    }
    strcpy(retVal[1],antwort);
    //printf("Speichere Antwort:%s\n",antwort);
    return retVal;
}

/**
 * Speichert eine Vokabel in der Liste
 * @param vokabeln - String der Vokabel
 * @param id
 * @param anfang
 */
void vokabelInListeZufuegen(char frage[standardBufferSize], char antwort[standardBufferSize], int id, struct vokabel* anfang) {
    //Vokabel in Liste aufnehmen
    struct vokabel* temp = anfang;
    if(anfang == NULL){
        printf("chillig");
        anfang = neueVokabelStruct(id,frage,antwort,temp);
    }else{
        while(temp->next != NULL){
            printf("%d",temp->id);
            temp = temp->next;
        }
    }
    //printf("Letzes Listenelement:%d\n",temp->id);
    temp->next = neueVokabelStruct(id,frage,antwort,temp);
    //TODO: Speichert nicht in die Liste???? Debugger fixen
}

/**
 * Erstellt eine neue Vokabel-Struktur
 * @param id
 * @param frage
 * @param antwort
 * @param prev
 * @return
 */
struct vokabel* neueVokabelStruct(int id, char frage[standardBufferSize], char antwort[standardBufferSize],struct vokabel* prev){
    struct vokabel* neueVokabel = malloc(sizeof(struct vokabel));
    neueVokabel->id = id;
    strcpy(neueVokabel->antwort,antwort);
    strcpy(neueVokabel->frage,frage);
    neueVokabel->prev = prev;
    neueVokabel->next = NULL;
    return neueVokabel;
}

void vokabelListeAusgeben(struct vokabel* erstesElement){
    struct vokabel* temp = erstesElement;
    printf("Gebe Liste aus\n");
    while (temp->next != NULL){
        printf("-------------\n");
        printf("%d\n",temp->id);
        printf("%s\n",temp->frage);
        printf("%s\n",temp->antwort);
        printf("-------------\n");
        temp = temp->next;
    }
}

void vokabelEinlesen() {

}

void vokabelZufuegen() {

}

void vokabelLoeschen() {

}

void vokabelnSpeichern() {

}

void error(char errorDesc[standardBufferSize]) {
    fprintf(stderr, "%s", errorDesc);
}



#include <stdio.h>
#include <stdlib.h>
#include <f2fs_fs.h>
#include "main.h"

struct vokabel *
neueVokabelStruct(int id, char frage[standardBufferSize], char antwort[standardBufferSize], struct vokabel *prev);

void vokabelInListeZufuegen(char frage[standardBufferSize], char antwort[standardBufferSize], struct vokabel *anfang);

void error(char errorDesc[standardBufferSize]);

char **vokabelEinlesenDecode(char vokabeln[standardBufferSize]);

bool wollenSieWirklichLoeschen();

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
            char **retVal = vokabelEinlesenDecode(vokabeln[i - 1]);
            if (retVal == NULL) {
                //error("Datei fehlerhaft!\n");
                continue;
            }
            char *frage = retVal[0];
            char *antwort = retVal[1];
            vokabelInListeZufuegen(frage, antwort, first);
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
char **vokabelEinlesenDecode(char vokabeln[standardBufferSize]) {
    int delimterIndex = 0;
    char frage[standardBufferSize] = "\0";
    char antwort[standardBufferSize] = "\0";
    //char retVal[2][standardBufferSize];
    char **retVal = malloc(2 * sizeof(char *));
    retVal[0] = malloc(sizeof(char[standardBufferSize]));
    retVal[1] = malloc(sizeof(char[standardBufferSize]));

    //Plausi
    int semiCount = 0;
    for (int i = 0; i < strlen(vokabeln); ++i) {
        if (vokabeln[i] == ';') {
            semiCount++;
        }
    }
    if (semiCount > 1) {
        error("Zeile enthaelt mehr als 1 Semikolon!\n");
        return NULL;
    } else if (semiCount == 0) {
        error("Zeile enthaelt kein Semikolon!\n");
        return NULL;
    } else if (strlen(vokabeln) < 3) {
        error("Zeile invalide!\n");
        return NULL;
    }

    //Frage einlesen
    for (int v = 0; v < standardBufferSize; ++v) {
        if (vokabeln[v] == ';') {
            delimterIndex = v;
            break;
        } else {
            frage[v] = vokabeln[v];
        }
    }
    strcpy(retVal[0], frage);
    //printf("Speichere Frage:%s\n",frage);

    //Antwort einlesen
    int arrCnt = 0;
    for (int j = delimterIndex + 1; j < standardBufferSize; ++j) {
        if (vokabeln[j] == '\n') {
            break;
        } else {
            antwort[arrCnt++] = vokabeln[j];
        }
    }
    strcpy(retVal[1], antwort);
    //printf("Speichere Antwort:%s\n",antwort);
    return retVal;
}

/**
 * Speichert eine Vokabel in der Liste
 * @param vokabeln - String der Vokabel
 * @param id
 * @param anfang
 */
void vokabelInListeZufuegen(char frage[standardBufferSize], char antwort[standardBufferSize], struct vokabel *anfang) {
    struct vokabel *temp = anfang;
    if (anfang->id == -1) {
        printf("Setzte erste Vokabel\n");
        anfang->id = 0;
        strcpy(anfang->frage, frage);
        strcpy(anfang->antwort, antwort);
        anfang->prev = NULL;
        anfang->next = NULL;
    } else {
        //Gehe bis zur letzten Vokabel
        int newID = 1; //Startet mit dem ersten Element nach Anfang
        while (temp->next != NULL) {
            temp = temp->next;
            newID++;
        }
        //printf("Letzte Vokabel-ID:%d\n", temp->id);
        temp->next = neueVokabelStruct(newID, frage, antwort, temp);
    }
}

/**
 * Erstellt eine neue Vokabel-Struktur
 * @param id
 * @param frage
 * @param antwort
 * @param prev
 * @return
 */
struct vokabel *
neueVokabelStruct(int id, char frage[standardBufferSize], char antwort[standardBufferSize], struct vokabel *prev) {
    struct vokabel *neueVokabel = malloc(sizeof(struct vokabel));
    neueVokabel->id = id;
    strcpy(neueVokabel->antwort, antwort);
    strcpy(neueVokabel->frage, frage);
    neueVokabel->prev = prev;
    neueVokabel->next = NULL;
    return neueVokabel;
}

/**
 * Gibt alle Vokabeln aus (Laufzeit)
 * @param erstesElement - erstes Listenelement
 */
void vokabelListeAusgeben(struct vokabel *erstesElement) {
    struct vokabel *temp = erstesElement;
    printf("Gebe Liste aus\n");
    while (temp != NULL) {
        printf("-------------\n");
        printf("ID:%d\n", temp->id);
        printf("Frage:%s\n", temp->frage);
        printf("Antwort:%s\n", temp->antwort);
        temp = temp->next;
    }
}

/**
 * Appended eine Vokabel an die Liste
 * @param erstesElement
 * @param vokabel
 */
void vokabelZufuegen(struct vokabel *erstesElement, char vokabel[standardBufferSize]) {
    char **retVal = vokabelEinlesenDecode(vokabel);
    if (retVal == NULL) {
        error("Fehler beim zufuegen!\n");
    } else {
        char *frage = retVal[0];
        char *antwort = retVal[1];
        vokabelInListeZufuegen(frage, antwort, erstesElement);
        free(antwort);
        free(frage);
    }
    free(retVal);
}

/**
 * Durchsucht die Liste und loescht einen Eintrag
 * @param vokabel
 * @param listeFirst
 */
struct vokabel *vokabelLoeschen(char vokabel[standardBufferSize], struct vokabel *listeFirst) {
    struct vokabel *temp = listeFirst;
    while (temp != NULL) {
        if (strcmp(temp->frage, vokabel) == 0 || strcmp(temp->antwort, vokabel) == 0) {
            if (wollenSieWirklichLoeschen(temp->frage, temp->antwort)) {
                if (temp->prev == NULL && temp->next == NULL) {
                    error("Kann das letzte Element der Liste nicht löschen!\n");
                    break;
                } else if (temp->prev == NULL) {
                    listeFirst = temp->next; //Anfang der Liste verschieben
                    if (temp->next->prev != NULL) {
                        temp->next->prev = NULL;
                    }
                    free(temp);
                } else if (temp->next == NULL) {
                    if (temp->prev->next != NULL) {
                        temp->prev->next = NULL;
                    }
                    free(temp);
                } else {
                    temp->next->prev = temp->prev;
                    temp->prev->next = temp->next;
                    free(temp);
                }
            }
        }
        temp = temp->next;
    }
    return listeFirst;
}

/**
 * Fragt ob der user wirklich loeschen will
 * @return - Wenn Eingabe y oder Y -> 1 sonst -> 0
 */
bool wollenSieWirklichLoeschen(char frage[standardBufferSize], char antwort[standardBufferSize]) {
    char var[standardBufferSize];
    printf("----> 	Wollen sie %s;%s wirklich loeschen? (Y/N)	 <----\n", frage, antwort);
    fgets(var, standardBufferSize, stdin);
    strtok(var, "\n");
    if (var[0] == 'y' || var[1] == 'Y') {
        return 1;
    }
    return 0;
}

/**
 * Speichert die Liste mit allen Vokabeln in eine Datei
 * @param listeFirst - Liste
 * @param name - Dateiname
 */
void vokabelnSpeichern(struct vokabel *listeFirst, char name[standardBufferSize]) {
    FILE *datei = fopen(name, "w");
    if (datei == NULL) {
        error("Datei konnte nicht erstellt werden!\n");
    } else {
        struct vokabel *temp = listeFirst;
        while (temp->next != NULL) {
            printf("Schreibe in Datei:%s;%s\n", temp->frage, temp->antwort);
            fprintf(datei, "%s;%s\n", temp->frage, temp->antwort);
            temp = temp->next;
        }
    }
}

void vokabelAbfragen(struct vokabel *liste) {
    struct vokabel *temp = liste;
    int count = 1;
    while (temp->next != NULL) {
        count++;
        temp = temp->next;
    }
    int random = rand() % count;
    temp = liste;
    for (int i = 0; i < random; ++i) {
        temp = temp->next;
    }
    printf("Frage: %s\n", temp->frage);
    char antwort[standardBufferSize];
    fgets(antwort, standardBufferSize, stdin);
    strtok(antwort, "\n");
    if (strcmp(antwort, temp->antwort) == 0) {
        printf("Richtige Antwort!\n");
    } else {
        printf("Falsche Antwort! - Richtig wäre: %s\n", temp->antwort);
    }
}

/**
 * Fehlermeldungen ausgeben
 * @param errorDesc - Meldung
 */
void error(char errorDesc[standardBufferSize]) {
    fprintf(stderr, "%s", errorDesc);
}



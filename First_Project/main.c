#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXT_FILE "/Users/astemir/Desktop/SchoolList /school_list.txt"
#define MAX_NAME 50
#define MAX_FACH 50
#define MAX_SCHUELLER 50            //definiere maximale String Name, Anzahl von Faechern und Schuellern



//erstelle Struktur Fach
typedef struct Fach {
    char fachName[MAX_FACH];
    float Note;
} Fach;


//erstelle Struktur Schueller mir array von Faechern
typedef struct Schueller {
    int ID;
    char name[MAX_NAME];
    Fach fach[3];           //maximal 3 Faecher
    
} Schueller;


//Funktion um liste zu finden oder neu erstellen
int loadListe(Schueller schueller[]) {
    FILE* file = fopen(TEXT_FILE, "r");
    if (file == NULL) {
        printf("Keine vorhandene Schuellerliste gefunden. Es wird eine neue Datei erstellt.\n");
        return 0;
    }
    
    int schuellerCount = 0;
    while (fscanf(file, "%d,%49[^,],%49[^,],%f,%49[^,],%f,%49[^,],%f", &schueller[schuellerCount].ID, schueller[schuellerCount].name,
                schueller[schuellerCount].fach[0].fachName, &schueller[schuellerCount].fach[0].Note,
                schueller[schuellerCount].fach[1].fachName, &schueller[schuellerCount].fach[1].Note,
                schueller[schuellerCount].fach[2].fachName, &schueller[schuellerCount].fach[2].Note) == 8) {
        schuellerCount++;
        if(schuellerCount > MAX_SCHUELLER) {
            printf("Maximale Anzahl von Schuellern erreicht\n");
            break;
        }
    }
    fclose(file);
    return schuellerCount;
}


//Funktion speichert Schueller wenn sie durch anderen Funktionen manipulliert werden
void saveSchueller(Schueller schueller[], int* schuellerCount) {
    FILE* file = fopen(TEXT_FILE, "w");
    if (file == NULL) {
        printf("Fehler beim Speichern der Aufgaben.\n");
        return;
    }
    for (int i = 0; i < *schuellerCount; i++) {
        fprintf(file, "\n%d,%s,%s,%f,%s,%f,%s,%f", schueller[i].ID, schueller[i].name,
                schueller[i].fach[0].fachName, schueller[i].fach[0].Note,
                schueller[i].fach[1].fachName, schueller[i].fach[1].Note,
                schueller[i].fach[2].fachName, schueller[i].fach[2].Note);
    }
    fclose(file);
    printf("=============================================\n");
}

//Funktion um Schueller zu sortieren nach ihren Namen
void sortSchueller (Schueller schueller[], int schuellerCount){
    for (int i = 0; i < schuellerCount - 1; i++) {              //bubble-sort nach Namen
        for (int j = 0; j < schuellerCount - i - 1; j++) {
            if (strcmp(schueller[j + 1].name, schueller[j].name) < 0) {
                Schueller tmp = schueller[j + 1];
                schueller[j + 1] = schueller[j];
                schueller[j] = tmp;
            }
        }
    }
    saveSchueller(schueller, &schuellerCount);
}

//Funktion um Schueller zu sortieren nach ihren ID
void sortNachIdSchueller (Schueller schueller[], int schuellerCount){
    for (int i = 0; i < schuellerCount - 1; i++) {                  //bubble-sort nach ID
        for (int j = 0; j < schuellerCount - i - 1; j++) {
            if (schueller[j + 1].ID < schueller[j].ID) {
                Schueller tmp = schueller[j + 1];
                schueller[j + 1] = schueller[j];
                schueller[j] = tmp;
            }
        }
    }
    saveSchueller(schueller, &schuellerCount);
}

void showSortedListe(Schueller schueller[], int schuellerCount) {
    printf("=============================================\n");
    sortSchueller(schueller, schuellerCount);
    for (int i = 0; i < schuellerCount; i++) {
        printf("ID: %d | Name: %s | Fach: %s Note: %.1f | Fach: %s Note: %.1f | Fach: %s Note: %.1f\n",
               schueller[i].ID, schueller[i].name,
               schueller[i].fach[0].fachName, schueller[i].fach[0].Note,
               schueller[i].fach[1].fachName, schueller[i].fach[1].Note,
               schueller[i].fach[2].fachName, schueller[i].fach[2].Note);
    }
    sortNachIdSchueller(schueller, schuellerCount);
    printf("=============================================\n");
}

void showListe(Schueller schueller[], int schuellerCount) {
    printf("=============================================\n");
    if (schueller[0].ID == 0)
        printf("Liste ist leer\n");
    
    for (int i = 0; i < schuellerCount; i++) {
        printf("ID: %d | Name: %s | Fach: %s Note: %.1f | Fach: %s Note: %.1f | Fach: %s Note: %.1f\n",
               schueller[i].ID, schueller[i].name,
               schueller[i].fach[0].fachName, schueller[i].fach[0].Note,
               schueller[i].fach[1].fachName, schueller[i].fach[1].Note,
               schueller[i].fach[2].fachName, schueller[i].fach[2].Note);
    }
    sortNachIdSchueller(schueller, schuellerCount);
    printf("=============================================\n");
}



//Funktion um Schueller himzufuegen
void addSchueler(Schueller schueller[], int *schuellerCount) {
    if (*schuellerCount >= MAX_SCHUELLER) {                     //Wnn Liste voll ist, kann man keine Schueller mehr addieren
        printf("List ist voll. Mehr Schuellern kann nicht hinzugefuegt werden\n");
        return;
    }
    Schueller newSchueller;                     //neu Variable von Struktur erstellen
    if (*schuellerCount > 0) {
        newSchueller.ID = *schuellerCount + 1;
    } else newSchueller.ID = 1;

    printf("Gib die Name des Schuellers: ");
    scanf("%s", newSchueller.name);
    int result;
    while (getchar() != '\n');                   //console leer machen fuer naechste Eingabe
    for (int i = 0; i < 3; i++) {
        printf("Gib der %d. Fach: ", i+1);
        scanf("%s", newSchueller.fach[i].fachName);
        while (getchar() != '\n');
        printf("Gib die Note fuer Fach %s: ", newSchueller.fach[i].fachName);
        result = scanf("%f", &newSchueller.fach[i].Note);
        if (result != 1) {
            printf("=============================================\n");
            printf("Falsche Noteneingabe. Program started neu...\n");
            while (getchar() != '\n');
            break;
        }
    }
    schueller[*schuellerCount] = newSchueller;
    (*schuellerCount)++;
    saveSchueller(schueller, schuellerCount);
}

//Funktion um Noten zu aktialisieren
void notenAktualisieren(Schueller schueller[], int schuellerCount) {
    printf("=============================================\n");
    int eingabe, result, count = 0;
    printf("Bitte ID des Schuellers eingeben: ");
    do {
    result = scanf("%d", &eingabe);
        if (eingabe > schuellerCount) {                                         //exit falls eingegebene ID groesser als die Anzahl von schuellern
            printf("=============================================\n");
            printf("Falsche Eingabe\nProgramm neu started...\n");
            printf("=============================================\n");
            while (getchar() != '\n');
            return;
        }
        if (result != 1) {
            if (count > 4) {
                printf("Sie haben 5 mal ID falsch eingegeben.\n Programm wird neu gestartet...\n"); //pruefen um richtige ID einzugeben(keine char[])
                break;
            }
            printf("Falsche Eingabe, biite korrekte ID eingeben: ");
            while (getchar() != '\n');
            count++;
            continue;
        }
    
    } while (result != 1);
    while (getchar() != '\n');
    if (result == 1) {                                      //noch mal pruefe ob genau 1 Zahl(ID) eingegeben wurde
        sortNachIdSchueller(schueller, schuellerCount);     //sortiere nach ID um richtig Note zu aktualisieren(falls Schueler nach Namen sortiert) wurden)
    
        printf("Noten aktialisieren fuer %s\n", schueller[eingabe - 1].name);
        int result;
        for (int i = 0; i < 3; i++) {
            float note;
            printf("Note fuer Fach %s eingeben: ", schueller[eingabe - 1].fach[i].fachName);
            result = scanf("%f", &note);
            if(result != 1) {
                printf("Falsche Noteneingabe. Bitte korrekte Note eingeben");
                while (getchar() != '\n');
                continue;
            } else
            schueller[eingabe - 1].fach[i].Note = note;
        }
    }
    saveSchueller(schueller, &schuellerCount);
    printf("Aenderungen wurden gespeichert\n");
    printf("=============================================\n");
}


//Funktion um average Note zu berechnen
void avgNote(Schueller sculler[], int schuellerCount) {
    printf("=============================================\n");
    int eingabe, indexOfSchueller, result, count = 0;
    float sum, avg;
    printf("Bitte ID des Schuellers eingeben: ");
    do {
    result = scanf("%d", &eingabe);
        if (result != 1) {
            if (count > 4) {                                                                       //pruefen um richtige ID einzugeben(keine char[])
                printf("Sie haben 5 mal ID falsch eingegeben.\n Programm wird neu gestartet\n");
                break;
            }
            printf("Falsche Eingabe, biite korrekte ID eingeben: ");
            while (getchar() != '\n');
            count++;
            continue;
        }
    
    } while (result != 1);
    while (getchar() != '\n');
    if (eingabe > schuellerCount) {                                          //exit falls Eingabe groesser als Anzahl von Schuellern
        printf("=============================================\n");
        printf("Falsche Eingabe\nProgramm neu started...\n");
        printf("=============================================\n");
        return;
    }
    if (result == 1) {
        for (int i = 0; i < schuellerCount; i++) {
            if (sculler[i].ID == eingabe) {
                
                indexOfSchueller = i;
                    sum = sculler[i].fach[0].Note + sculler[i].fach[1].Note + sculler[i].fach[2].Note;
                    avg = sum / 3;
                    break;
            }
        }
    }
    printf("=============================================\n");
    printf("Durchschnittsnote von Schueller %s = %.1f\n", sculler[indexOfSchueller].name, avg);
    printf("=============================================\n");
}

//Hauptmenue
int main(void) {
    
    Schueller schueller[MAX_SCHUELLER];
    int schuellerCount = loadListe(schueller);
    
    int eingabe = 0;
    int result;
    printf("Wilkommen zu Notenverwaltungssystem\n");
    printf("=============================================\n");
    do {
        printf("1. Schueler hinzufuegen\n");
        printf("2. Noten aktualisieren\n");
        printf("3. Liste aller Schueller nach ID sortiert zeigen\n");
        printf("4. Liste aller Schueller nach Namen sortiert zeigen\n");
        printf("5. Durchschnittsnote berechnen\n");
        printf("6. Program beenden\n");
        
        printf("Bitte Zahl eingeben: ");
        result = scanf("%d", &eingabe);
    
        if (result != 1) {
            printf("=============================================\n");
            printf("Falsche Eingabe! Bitte eine Zahl eingeben.\n");
            printf("=============================================\n");
            
            while (getchar() != '\n');
            
            continue;
        } else {
            while (getchar() != '\n');
            switch (eingabe) {
                case 1:
                    printf("Schueler hinzufuegen\n");
                    addSchueler(schueller, &schuellerCount);
                    break;
                case 2:
                    printf("Noten aktualisieren\n");
                    notenAktualisieren(schueller, schuellerCount);
                    break;
                case 3:
                    printf("Liste aller Schueller zeigen\n");
                    showListe(schueller, schuellerCount);
                    break;
                case 4:
                    printf("Liste aller Schueller sortiert zeigen\n");
                    showSortedListe(schueller, schuellerCount);
                    break;
                case 5:
                    printf("Durchschnittsnote berechnen\n");
                    avgNote(schueller, schuellerCount);
                    break;
                case 6:
                    printf("Programm beenden\n");
                    break;
                default:
                    printf("=============================================\n");
                    printf("Falsche Eingabe, bitte korrekter Zahl eingeben\n");
                    printf("=============================================\n");
                    break;
            }
        }
    } while (eingabe != 6);
    
    printf("Program erfolgreich beendet\n");
    return 0;
}

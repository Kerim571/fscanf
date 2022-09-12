/**
 *	Projekt geforked von https://github.com/bjoekeldude/fscanf
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char const* const VERSIONSNR = "0.1.2";

int const DB_SIZE = 40;

struct vorfahren
{
	char vorname[20];
	char nachname[20];
};

struct gdatum
{
	int tag;
	int monat;
	int jahr;
};

struct tdatum
{
	int tag;
	int monat;
	int jahr;
};

struct person
{
	char vorname[20];
	char nachname[20];
	struct vorfahren vorfahre;
	struct gdatum geburtsdatum;
	struct tdatum todesdatum;
};
typedef struct person person_t;



void readcsv(char const* const datei)
{
    FILE* filepointer = NULL;
    int   zaehler     = 0;

    filepointer = fopen(datei, "r");
    if(NULL == filepointer)
    {
        fprintf(stderr, "Couldnt open file '%s'\n", datei);
        exit(2);
    }
    person_t stammbaum[DB_SIZE];
    while(fscanf(filepointer,
                 "%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%d,%d,%d,%s",
                 stammbaum[zaehler].vorname,
                 stammbaum[zaehler].nachname,
		 stammbaum[zaehler].vorfahre.vorname,
		 stammbaum[zaehler].vorfahre.nachname,
		 &stammbaum[zaehler].geburtsdatum.tag,
		 &stammbaum[zaehler].geburtsdatum.monat,
		 &stammbaum[zaehler].geburtsdatum.jahr,
		 &stammbaum[zaehler].todesdatum.tag,
		 &stammbaum[zaehler].todesdatum.monat,
		 &stammbaum[zaehler].todesdatum.jahr)
                 
          != EOF)
    {
        printf("\nName: %s, %s, \n Vorfahre: %s, %s \n Geburtsdatum: %d.%d.%d \n Todesdatum: %d.%d.%d",
     		  stammbaum[zaehler].vorname,
		  stammbaum[zaehler].nachname,
		  stammbaum[zaehler].vorfahre.vorname,
		  stammbaum[zaehler].vorfahre.nachname,
		  &stammbaum[zaehler].geburtsdatum.tag,
		  &stammbaum[zaehler].geburtsdatum.monat,										  &stammbaum[zaehler].geburtsdatum.jahr,								                  &stammbaum[zaehler].todesdatum.tag,
		  &stammbaum[zaehler].todesdatum.monat,
		  &stammbaum[zaehler].todesdatum.jahr);
        zaehler++;
        if(zaehler == DB_SIZE)
        {
            fprintf(stderr, "Datenbank voll! \n");
            break;
        }
    }
    // check if file closed correctly
    if(fclose(filepointer) == EOF)
    {
        fprintf(stderr, "Fehler beim schließen der Datei! \n");
        exit(2);
    }
}
int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "No option recognized. Wrong Usage. Please try -h\n");
    }

    while(true)
    {
        int option = getopt(argc, argv, "hvf:");
        switch(option)
        {
        case 'h':
            printf("Bitte -f nutzen um einen File-Path anzugeben\n");
            exit(0);

        case 'v':
            printf("Version %s\n", VERSIONSNR);
            exit(0);

        case 'f':
            readcsv(optarg);
            break;

        case '?':
            fprintf(stderr, "Please try -h\n");
            exit(1);

        case -1:
            exit(0);
        }
    }

    return 0;
}

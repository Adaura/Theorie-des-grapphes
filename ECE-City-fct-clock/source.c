#include <stdio.h>
#include <time.h>
#include "fct.h"
#include <windows.h>
#define ATTENDRE(temps) Sleep(temps*1000)



void date(){
    time_t secondes;
    struct tm instant;//structure pres def dans time.h avec en elements l'année le mois le jour etc

    time(&secondes);
    instant=*localtime(&secondes);

    printf("%d/%d/%d ; %d:%d:%d\n", instant.tm_mday, instant.tm_mon+1,instant.tm_year+1900, instant.tm_hour, instant.tm_min, instant.tm_sec);
    printf("%s\n", ctime(&secondes));
}

void tps_depause(){
    time_t depart, arrivee;
    time(&depart);

    printf("vous avez mis le jeux en pause\n");
    getchar();

    time(&arrivee);
    printf("Vous vous etes absente pendant %f secondes.\n", difftime(arrivee, depart));

}

void Clock(){
    int i=0;
    do {
        i++;
        date();
        ATTENDRE(1);
    }while(i<100);
}


void ECEflooz(){
    int flooz=500000;

}

int cycle(){
    int i;
    time_t t0;
    time(&t0);
    int nbcycle;
    do {
        i++;
        time_t instant;
        time(&instant);
        if (difftime(instant, t0) == 15) {
            nbcycle++;
            t0=instant;

        }
        ATTENDRE(1);
    }while(i<46);
    return nbcycle;
}
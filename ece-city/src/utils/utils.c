#include <stdio.h>

const char* secondsToTime(int seconds){
    int hours = seconds/3600;
    int minutes = (seconds - hours*3600)/60;
    int sec = seconds - hours*3600 - minutes*60;

    char *formattedTime;
    sprintf(formattedTime, "%dh:%dm:%ds", sec, minutes, hours);
    return formattedTime;
}
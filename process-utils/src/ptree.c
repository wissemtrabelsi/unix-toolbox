//
// Created by Wissem Trabelsi
//

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#ifdef __linux__

int do_ptree(int argc, char *argv[]){
    if (argc != 2){
        print_error("Usage: ptree <pid>\n",NULL);
        return 1;
    }
    char path[256];
    snprintf (path, sizeof(path),"/proc/%s/status", argv[1]);
    char line [256];// convention power of 2
    FILE *fptr;
    fptr=fopen(path, "r");
    if (fptr ==NULL){
        print_error("Error opening /proc status for PID", NULL);
        return 1;
    }

    while(fgets(line,sizeof(line), fptr) != NULL)
    {
        // compare only first n characters // STRNCMP
        if( strncmp(line, "Pid:", 4) == 0 || strncmp(line, "State:", 6) == 0 || 
            strncmp(line, "Name:", 5) == 0 || strncmp(line, "PPid:", 5) == 0){
                printf("%s", line);
            }
    }
    fclose(fptr);
return 0;
}
#else //mac os other
int do_ptree(int argc, char *argv[]){
    (void) argc;// void is used to supress unuesr parameter warning
    (void) argv;
    print_error("ptree in a linux only supported command\n", NULL);
    return 1;
}
#endif 
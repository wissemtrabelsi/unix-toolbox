//
// Created by Wissem Trabelsi
//
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <signal.h>// kill SIG....
#include <string.h>// strcmp
#include <dirent.h>//opendir readdir
#include <stdlib.h>
#include "utils.h"

#ifdef __linux__

static int get_signal(const char *name){
    if (strcmp(name, "SIGINT") == 0){
        return SIGINT;
    }
    else if (strcmp(name, "SIGKILL") == 0){
        return SIGKILL;
    }
    else if (strcmp(name, "SIGTERM") == 0){
        return SIGTERM;
    }
    else if (strcmp(name, "SIGSTOP") == 0){
        return SIGSTOP;
    }
    else if (strcmp(name, "SIGCONT") == 0){
        return SIGCONT;
    }else{
        return -1;
    }
}

int do_sig (int argc, char *argv[]){
    if (argc != 3 ){
        print_error("Usage: sig <signal> <Process name>\n",NULL);
        return 1;
    }

    int signum=get_signal(argv[1]);
    if (signum == -1) {
        print_error("Error: unknown signal",argv[1]);
        return 1;
    }
    DIR *dir = opendir("/proc");
    if (dir == NULL){
        print_error("Error: cannot open /proc",NULL);
        return 1;
    }

    struct dirent *entry;
    int found = 0;

    while ( (entry = readdir(dir)) != NULL)
    { //give me the next PID folder

        if(entry -> d_name[0] < '0' || entry -> d_name[0] > '9'){
            continue;
        }
        //path building
        char path[256];
        //build a string
        snprintf(path, sizeof(path), "/proc/%s/status", entry -> d_name);

        FILE *fi=fopen(path, "r");
        if (fi == NULL) continue;
        
        char line [256];
        while (fgets(line, sizeof(line), fi) != NULL)
        {
            if (strncmp(line, "Name:", 5) == 0){
                //linux kernel always writes /proc/PID/status
                //in this format Name:[ TAB ]firefox\n
                char name[256];
                sscanf(line, "Name:\t%255s", name);//extract/read value from text
                
                if (strcmp(name, argv[2]) == 0){
                    int pid = atoi(entry -> d_name);//folder name = PID
                    kill(pid,signum);
                    printf("sent signal to %s (PID: %d)\n",argv[2], pid);
                    found += 1;
                }
            }
        }
        fclose(fi);
    }
    closedir(dir);
    if (found == 0){
        print_error("Erro: process not found", argv[2]);
        return 1;
    }

    return 0;
}
#else
int do_sig (int argc, char* argv[]){
    (void) argc;
    (void) argv;
    print_error("sig is only available on linux", NULL);
    return 1;
}
#endif
//
// Created by Wissem Trabelsi
//

#define _POSIX_C_SOURCE 200809L
#include <signal.h> //define SIGINT 2 SIGTERM 15
#include <stdlib.h> // atoi.h
#include <unistd.h> // fork, execvp, sleep
#include <sys/wait.h> // wait
#include <stdbool.h>
#include <string.h> // memset
#include "utils.h"

void my_handler(int signum){
    if (signum == SIGINT){
        print_error("Stopping pwatch CTRL+C",NULL);
        exit (0); // terminates process
    }
    if (signum == SIGTERM){
        print_error("Stopping pwatch",NULL);
        exit (0);
    }
}

int do_pwatch(int argc, char *argv[]){

    if (argc <3){
        print_error("Usage: pwatch <interval> <command> [args]\n",NULL);
        return 1;
    }
    int interval=atoi(argv[1]); // "" to int
    if (interval <= 0){
        print_error("Error: Interval should be positive number \n",NULL);
        return 1;
    }

    char **command = &argv[2];
    struct sigaction sig;
    
    // clear the structure memory = good practice
    // prevents garbage values from causing weird behavior
    // Sets all bytes to 0 before using it. Good practice like in c variables
    memset(&sig, 0, sizeof(sig));
    
    // set handler function
    // i used an adress to this funtion
    // so it s like 
    // here's my number, call me when SIGINT or.. arrives
    // NOTTT  "call me RIGHT NOW" with ()
    // the OS call it later when signal arrives
    sig.sa_handler = my_handler;
    // sa_handler is a function pointer — it stores an address to call later. So you give it the address,

    // The mask controls which signals are blocked WHILE your handler is running.
    // sigemptyset` sets it to empty — don't block any extra signals during handling.
    // initialize the mask (dont block any extra signals for now)
    sigemptyset(&sig.sa_mask);
    

    // register handler for SIGINT (Ctrl+C) and SIGTERM (kill command)
    // both signals use the same handler defined in sig.sa_handler
    sigaction(SIGINT, &sig, NULL);
    sigaction(SIGTERM, &sig, NULL);

    while (true){ // only the parent goes back to the top
        pid_t pid=fork(); // at this line two processes are born simultaneously running
        /*
            what fork returns is:
            parent get: pid=3212 and child gets pid =0
        */
        // pid is the returning value of pid
        if (pid ==0){
            // i am the child fork gave me 0
            // here execvp run the child
            execvp(command[0], command); // command[0] = "ls"
            
            // execvp returns only if it fails,-1 
            // if we reach here execvp failed
            print_error("Error: command not found", NULL);
            exit (1); // kill child
        }
        else{ // im the parent fork gave me child pid
             // makes the parent pause/block until the child finishes.
            wait(NULL); // makes the parent pause/block until the child finishes.
            // I don't care about the exit status of the child — just wait for it to finish.
            sleep(interval);
        }
    }
    
    return 0;
}
/*
pwatch uses the Unix fork-exec pattern. The parent process forks a child,
the child executes the command, and the parent waits for it to finish.
This repeats every N seconds.
This way the parent process is never replaced — only the child gets exec'd.
 */
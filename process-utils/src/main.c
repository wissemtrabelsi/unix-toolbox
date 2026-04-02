//
// Created by Wissem Trabelsi
//
#include <string.h> // strcmp
#include <unistd.h> // write
#include "utils.h"
#include "sig.h"
#include "ptree.h"
#include "pwatch.h"


static void print_usage(void){

    const char *usg_msg=
    "Usage: putil <command> [args]\n"
    "\nCommands:\n"
    "  pwatch <interval> <command>     - run command every N seconds\n"
    "  ptree  <pid>                    - show process info from /proc\n"
    "  sig    <signal> <process_name>  - send signal to process by name\n"
    "  --help                          - show this message\n";
    write(2,usg_msg,my_strlen(usg_msg));
}
int main(int argc, char *argv[]){

    if (argc < 2){
        print_usage();
        return 1;
    }
    if(strcmp(argv[1], "ptree") == 0){
        return do_ptree(argc -1, argv + 1);
    }
    else if (strcmp(argv[1], "pwatch") == 0)
    {
        return do_pwatch(argc -1, argv + 1);
    }
    else if (strcmp(argv[1], "sig") == 0)
    {
        return do_sig(argc -1, argv + 1);
    }
    else if(strcmp(argv[1], "--help") == 0)
    {
        print_usage();
        return 0;
    }
    else{
        print_error("Unknown command",NULL);
        print_usage();
        return 1;
    }
    
    

}
//
// Created by Wissem Trabelsi
//

#include <stdio.h>
#include <sys/stat.h>
#include "utils.h"

int do_attrib(int argc, char *argv[])
{
    if (argc != 2)
    {
        print_error("Usage: attrib <filename>\n", NULL);
        return 1;
    }
    struct stat st;

    if (stat(argv[1],&st) < 0)
    {
        perror(argv[1]);//prints system error
        return 1;
    }

    printf("File Type: %o\n", st.st_mode); //%o octal
    char buf[32];
    format_size(st.st_size,buf,sizeof(buf));
    printf("File size: %s \n", buf); //long int
    printf("Permissions: %o \n", st.st_mode);
    printf("Number of hard links: %hu \n", st.st_nlink); //unsigned short
    printf("Last modified time: %ld \n", st.st_mtime);


    return 0;
}
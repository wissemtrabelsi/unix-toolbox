//
// Created by Wissem Trabelsi
//

#include <stdio.h>
#include <sys/stat.h>
#include "utils.h"

int attribute(char *filename)
{
    struct stat st;


    if (stat(filename,&st) < 0)
    {
        perror(filename);//prints system error
        return 1;
    }

    printf("File Type: %o\n", st.st_mode); //%o octal
    char buf[32];
    format_size_h(st.st_size,buf,sizeof(buf));
    printf("File size: %s\n", buf); //long int
    printf("Permissions: %o\n", st.st_mode);
    printf("Number of hard links: %lu\n", st.st_nlink); //unsigned long
    printf("Last modified time: %ld\n", st.st_mtime);


    return 0;
}
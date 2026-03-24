//
// Created by Wissem Trabelsi
//

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

void reverse(char *s)
{
    char c;
    size_t len = my_strlen(s);
    for (size_t i = 0; i < (len / (2)); i++)
    {
        c = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = c;
    }
}

int do_reverse(int argc ,char **argv)
{
    if (argc != 2)
    {
        print_error("Usage: ./reverse filename\n",NULL);
        return 1;
    }
    int fd =open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        print_error("cannot open file\n",NULL);
        return 1;
    }
    FILE *f = fdopen(fd,"r");
    if (f == NULL)
    {
        print_error("fdopen failed\n",NULL);
        close(fd);
        return 1;
    }

    char *line = NULL;
    size_t len = 0;

    while (getline(&line,&len,f) != -1)//How much memory is allocated for the buffer — the maximum it can hold.
    //-1 on EOF or error
    {
        size_t line_len = my_strlen(line);
        if (line_len > 0  && line[ line_len - 1] == '\n')
        {
            line[ line_len - 1] = '\0';
        }
        reverse(line);
        write(1,line,my_strlen(line));
        write(1,"\n",1);
    }
    free(line);//getline() automatically allocates memory on the heap
    fclose(f);
    return 0;
}


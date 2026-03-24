//
// Created by Wissem Trabelsi
//
#include "utils.h"
#include <unistd.h>//for write
// Calculates string length without using strlen()
size_t my_strlen(const char *str)
{
    size_t len = 0;//unsigned type (never negative)
    while (str[len])
        len++;
    return len;
}

// Prints an error message with an optional filename to stderr
void print_error(const char *msg, const char *filename)
{
    write(2, msg, my_strlen(msg));
    if (filename) {
        write(2, filename, my_strlen(filename));
        write(2, "\n", 1);
    }
}
//
// Created by Wissem Trabelsi
//

#include "utils.h"
#include <unistd.h>//for write
#include <stdio.h>
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
    if (filename) {//!= NULL print it.
        write(2, filename, my_strlen(filename));
        write(2, "\n", 1);
    }
}

// converts bytes to human readable string (KiB/MiB/GiB)
// (double) cast ensures decimal division instead
void format_size_h(off_t size, char *buf, size_t buf_len)
{
    //only switch units when the number is actually readable in the next unit
    if (size < 2048)
    {
        snprintf(buf, buf_len, "%ld Bytes", (long)size);
    }
    //Threshold = has the file reached 2048 of the current unit? → if yes, move to the
    else if (size < 2048 * 1024)//
    {
        snprintf(buf,buf_len,"%.2f KiB", (double)size / 1024);
    }
    // LL suffix forces 64-bit arithmetic for GiB/TiB thresholds to prevent int overflow
    else if (size < 2048LL * 1024 * 1024)
    {
        snprintf( buf,buf_len,"%.2f MiB", (double)size / (1024*1024));
    }
    // threshold: the boundary that decides which unit to use
    // conversion: the division that transforms bytes into that unit
    // example: threshold = size < 2048*1024 → conversion = size/1024 → KiB
    else if (size < 2048LL * (1024*1024*1024))
    {
        snprintf(buf,buf_len,"%.2f GiB", (double)size / (1024*1024*1024) );
    }
    else
    {
        snprintf(buf,buf_len,"%.2f TiB", (double)size / (1024LL*1024*1024*1024));//prevent overflow
    }
}
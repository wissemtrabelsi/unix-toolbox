//
// Created by Wissem Trabelsi
//

#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>//for size_t
#include <sys/stat.h>// defines off_t, used by struct stat fields like st_size
size_t my_strlen(const char *str);
void print_error(const char *msg, const char *filename);
//size: file size in bytes from st.st_size (off_t matches stat's type)
//buf: buffer where result string will be written e.g "4.2 GiB"
//buf_len: size of buf, prevents buffer overflow
void format_size(off_t size, char *buf, size_t buf_len);
#endif //UTILS_H
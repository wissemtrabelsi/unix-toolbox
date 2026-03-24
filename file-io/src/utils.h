//
// Created by Wissem Trabelsi
//
#ifndef UTILS_H
#define UTILS_H
#include  <stddef.h> //for size_t

size_t my_strlen(const char *str); //const:prevent modifying str content
void print_error(const char *msg, const char *filename);
#endif //UTILS_H
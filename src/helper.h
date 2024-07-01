#ifndef HELPER_H
#define HELPER_H
#include "ask.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "users.h"
#include "questions.h"



int     show_menu(vector* content);
void    split_string(char* str, const char* dilem, vector* v);
void    read_from_file(const char* file_name, vector *vec);
void    write_to_file(FILE* file_name, const char* fmt, ...);
char*   to_str(void* number);
int     to_int(char* str);
size_t  str_len(const char* s);




#endif // HELPER_H

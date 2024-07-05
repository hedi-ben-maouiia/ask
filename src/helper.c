#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "ask.h"


//write string to file 
size_t show_menu(vector* content)
{
    printf("\nMenu: \n");
    for(size_t i=0; i < content->size; ++i){
        printf("\t\t%zu) %s.\n",i+1,(char*)content->users[i]);
    }
    printf("\nEntr a choice in range 1 - %zu: ",content->size);
    size_t choice = 0;
    scanf("%zu",&choice);
    while(1 > choice || choice > content->size){
        printf("\nPleas enter a valid choice: ");
        choice = 0;
        scanf("%zu",&choice);
    }
    return choice;
}
void write_to_file(FILE* file_name, const char* fmt, ...)
{   
    va_list ap;
    va_start(ap,fmt);
    vfprintf(file_name,fmt,ap);
    va_end(ap); 
}

void split_string(char* str, const char* dilem, vector* v)
{
    char* token =  strtok(str,dilem); 
    while(token != NULL){
        append(v,(void*)token);
        token = strtok(NULL,dilem); 
    }
}

void read_from_file(const char* file_path, vector* vec)
{
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: cannot open file to read\n");
        exit(1);
    }
    char *buffer = malloc(sizeof(char)* 100);   
    while(fgets(buffer,100,file)){
        buffer[strcspn(buffer,"\n")] = '\0';
        append(vec,(void*)strdup(buffer));
        memset(buffer,0,100);
    }
    free(buffer);
    fclose(file);
}

char* to_str(void* number)
{
    int n = *(int*)number;
    char is_neg = 0;    
    if(n < 0){
        n = -n;
        is_neg = 1;
    }
    size_t digits = 0; 
    while(*(int*)number /= 10)                              // get how many degits in the number
        digits++;
    char* str = (char*) malloc(sizeof(char) * digits + 2);  // allocate the need size the string  + 2 for the null terminator and (-) sign if it's negative number
    if(is_neg)
        str[0] = '-', digits++;
    size_t len = digits;  
    while(n){
        str[digits--] = (n%10) + '0'; 
        n /= 10;
    }    
    str[len+1] = '\0';
    char* ret = strdup(str);
    free(str);
    return ret; 
}

size_t str_len(const char* s)
{
    size_t len = 0;
    while(*s++)
        len++;
    return len;
}

int  to_int(char* str)
{
    size_t len = str_len(str);
    int num = 0;
    int coff = 1;
    for(int i = len-1;i > 0;--i){
        num += (str[i] - '0') * coff; 
        coff *= 10; 
    }
    if(str[0] == '-')
        return -num;
    return (num + (str[0] - '0') * coff);
}




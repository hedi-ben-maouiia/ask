#ifndef ASK_H_
#define ASK_H_ 
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include"vector.h"

#define LINE_BUFFER_SIZE 1024

typedef struct {
    size_t user_id;
    char*  user_name;
    char*  user_email;
    char*  password;
    int    is_ananymose;
}user_info;

typedef struct {
    size_t quition_id;      
    size_t quition_from_id; 
    size_t quition_to_id;   
    char*  quition;
    char*  answer;
}quistion_info;


void read_from_file(const char* path,vector* v);
void write_to_file(const char* path, vector* v, bool apend);
void split_string(char *str,vector * v,const char delim);     
int  print_menu(vector* v);

//TODO:
void user_init(user_info* u, char* str);
void quistion_init(quistion_info* q, char* str);



#endif

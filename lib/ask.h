#ifndef ASK_H_
#define ASK_H_ 
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include"vector.h"

#define LINE_BUFFER_SIZE 1024

static size_t USER_ID = 0;
static size_t QUISITON_ID = 0;


typedef struct {
    size_t user_id;
    char*  name; 
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


void  read_from_file(const char* path,vector* v);
void  write_to_file(const char* path, vector* v, bool apend);
void  split_string(char *str,vector * v,const char delim);     
int   to_int(char* str);
char* to_str(int n);
int   print_menu(vector* v);
char* user_to_string(user_info* new_user);
char* quition_to_string(quistion_info* new_quitions);

user_info* user(user_info* new_user);       // initialize new_user with empty value
void  user_init(user_info* u, char* str);   // initialize an already user existed
void  quistion_init(quistion_info* q, char* str);

void run_system(void);

#endif

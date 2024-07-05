#ifndef USERS_H
#define USERS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


typedef struct {
    char*     name;
    char*     user_name;
    char*     email;
    char*     password;
    size_t    user_id;
    int       is_anonymous;
} user;


#include "ask.h"

void sign_up(user* cur_user,
             vector *users,
             vector *questions,
             vector *users_line,
             vector *questions_line,
             vector* splited_string);
void login(user* cur_user,
           vector* users,
           vector* questions,
           vector* users_line,
           vector* questions_line,
           vector* splited_string);
char*   user_to_string(user *user);
void    user_init(user* user,vector *v);
void    print_user(user *user);
size_t  get_user_id(user *user);
char*   get_user_name(vector *users,int id);
char*   get_user_pass(user *user);
void    update_users(user* user);
int     used_user_name(char* u,vector*users);
int     allow_anonymous(int id,vector *users);
void    input(char* data,size_t *size);
void    clean_buffer(void);


#endif  // USERS_H

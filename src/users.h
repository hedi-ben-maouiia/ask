#ifndef USERS_H
#define USERS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "ask.h"


typedef struct {
    char*     name;
    char*     user_name;
    char*     email;
    char*     password;
    size_t    user_id;
    int       is_anonymous;
} user;


void    login(user* cur_user, vector* users);
void    sign_up(user* cur_user,vector* users, vector* usInfo);
char*   user_to_string(user *user);
void    user_init(user* user,vector *v);
void    print_user(user *user);
size_t  get_user_id(user *user);
char*   get_user_name(user *user);
char*   get_user_pass(user *user);
void    update_users(user* user);
int     used_user_name(char* u,vector*users);


#endif  // USERS_H

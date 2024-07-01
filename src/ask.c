#include "ask.h"
#include "helper.h"
#include "users.h"
#include <stdio.h>
#include <stdlib.h>

void check_malloc_fail(void *p)
{
    if(p == NULL)
    { 
        fprintf(stderr,"ERROR: cannot reallocate memory\n");    
        exit(1);
    }
}

void resize(vector* vec)
{
    vec->capacity *= 2;
    vec->users = realloc(vec->users,( sizeof(void**) * vec->capacity)); 
    check_malloc_fail(vec->users);    
}

void append(vector *vec,void *user)
{
    if(vec->size >= vec->capacity) 
        resize(vec);
    vec->users[vec->size++] = user;
}

void vec_init(vector* vec, size_t cap)
{    
    vec->users      = malloc(sizeof(void*) * cap);
    check_malloc_fail(vec->users);
    
    vec->capacity   = CAPACITY;
    vec->size       = 0;
}
void free_vec(vector* v)
{
    for(size_t i=0; i < v->size; ++i)
    {
        free(v->users[i]);
    }
    free(v->users);
}
void empty_vec(vector* vec)
{
    vec->size = 0; 
}

void load_users(vector *users,vector *lines, vector*splited_string)
{
    read_from_file("users.txt", lines);
    user* curr_user;
    for(size_t i = 0; i < lines->size; ++i){
        curr_user = malloc(sizeof(user));
        check_malloc_fail(curr_user);
        split_string(lines->users[i],",",splited_string);        
        user_init(curr_user,splited_string);
        empty_vec(splited_string);
        append(users,(void*)curr_user);
    }
}

void print_users(vector*users)
{
    for(size_t i = 0; i < users->size; ++i)
        print_user((user*)users->users[i]);
}






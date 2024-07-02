#ifndef ASK_H
#define ASK_H
#include <stdio.h>
#include <stdlib.h>


#define CAPACITY 20


typedef struct {
    void        **users;
    size_t      size;
    size_t      capacity;
} vector;

void resize(vector* vec);
void append(vector *vec,void *user);
void vec_init(vector* vec, size_t cap);
void load_users(vector *users,vector *v, vector*vec);
void print_users(vector*users);
void empty_vec(vector* vec);
void check_malloc_fail(void *p);
void free_vec(vector* v);

#endif  // ASK_H

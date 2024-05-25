#ifndef VECTOR_H_
#define VECTOR_H_
#include <stdio.h>
#include <stdlib.h>

#define CAP_INIT 100

typedef struct{
    
    char **items;    
    int  size;
    int  capacity;

}vector;

// Helper function 
void shift_left(vector *);

// Function to operate on the vector 
void vector_init(vector* __vector);
void push_back(vector* __vector, char *);
void push_front(vector* __vector, char *);
void resize_vector(vector*  __vector,int cap);

void  set_at(vector* __vector, int __idx, char* __item);
void *get_at(vector* __vector, int __idx);

int  get_size(vector* __vector);
int  get_capacity(vector * __vector);
void print_vector(vector * __vector);
void vector_free(vector *);
#endif 

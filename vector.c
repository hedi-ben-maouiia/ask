#include <stdlib.h>
#include <string.h>
#include "lib/vector.h"




void vector_init(vector *v){
    v->size = 0;
    v->capacity = CAP_INIT; 
    v->items = malloc(sizeof(void *) * v->capacity);
} 

void resize_vector(vector *v,int capacity){
    capacity *= 2;
    void **items = (void *) realloc(v->items, sizeof(void *) * capacity);
    
    if(v->items == NULL){
        printf("ERROR: null pointer in resize_vector realloc()!\n");
        fprintf(stderr, "NULL in realloc!\n");
        exit(EXIT_FAILURE);
    }
    if(items){
        v->items = items;
        v->capacity = capacity;
    }

}

void push_back(vector *v, void* str){
    int size = get_size(v);
    int capa = get_capacity(v);
    if(size == capa){
        resize_vector(v,capa);
        v->items[v->size++] = str;
        return; 
    }
    v->items[v->size++] = str; 
}
void push_front(vector *v, void* str){
    int s,c; 
    s = get_size(v);
    c = get_capacity(v);
    
    if(s == c){
        resize_vector(v,c);
        shift_left(v);
        v->items[0] = str;
        v->size++;
        return; 
    }
    shift_left(v);
    v->items[0] = str;
    v->size++;
}
void set_at(vector *v, int idx, void* item){ 
    if(idx < 0 || idx > get_size(v)){
        printf("ERROR: Invalid index\n");
        exit(EXIT_FAILURE);
    }
    v->items[idx] = item;
}
void* get_at(vector *v, int idx){
    if(idx < 0 || idx > get_size(v)){
        printf("ERROR: Invalid index\n");
        return NULL; 
    }
    return v->items[idx]; 
}
int get_size(vector *v){
    return v->size; 
}

int get_capacity(vector *v){
    return v->capacity;
}
void vector_free(vector *v){
    free(v->items);
}
void print_vector(vector *v){
    int size = get_size(v); 
    for(int i=0;i < size;++i){
        printf("item[%d]=%s\n",i+1,(char*)v->items[i]);
    } 
    printf("\n");
}
void shift_left(vector* v){
    int size = get_size(v); 
    for(int i = size - 1; i > 0;--i)
       v->items[i+1] = v->items[i];      
}


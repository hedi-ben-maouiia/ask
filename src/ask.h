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
void load_data(vector *users,
               vector *questions,
               vector *users_line,
               vector *questions_line,
               vector* splited_line);


typedef struct p_to_thread
{
    int p_id;
    int thread_ids[CAPACITY];
} p_to_thread;

void p_to_thread_init(int p_id,int thread_ids[]);

#include "users.h"
#include "questions.h"

void ask_question(user *cur_user,vector* users,vector*questions);

void show_feed(vector *users,
               vector *questions,
               vector *users_line,
               vector *questions_line,
               vector *splited_string);

void print_users(vector*users);
void empty_vec(vector* vec);
void check_malloc_fail(void *p);
void free_vec(vector* v);
void answer_question(user* cur_users,vector *questions);
void show_quesion_for_me(user* cur_user,
                         vector *users,
                         vector *questions,
                         vector *users_line,
                         vector *questions_line,
                         vector *splited_string);
#endif  // ASK_H

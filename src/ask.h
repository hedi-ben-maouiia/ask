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

#include "users.h"
#include "questions.h"



void resize(vector* vec);
void append(vector *vec,void *user);
void vec_init(vector* vec, size_t cap);
void free_vec(vector* v);

void show_feed(vector *users,vector *questions);
void empty_vec(vector* vec);
void check_malloc_fail(void *p);

void load_data(vector *users,vector *questions,vector *users_line,vector *questions_line,vector* splited_line);
void print_question_to_me(user *cur_user,vector* users,vector* questions);
void print_question_from_me(user *cur_user,vector* users,vector* questions);
void ask_question(user *cur_user,vector* users,vector*questions);
void answer_question(user* cur_users,vector *questions);
void show_feed(vector* questions,vector* users);
void print_users(vector*users);

#endif  // ASK_H

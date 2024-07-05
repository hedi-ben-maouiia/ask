#ifndef QUESTION_H
#define QUESTION_H 


typedef struct {
    int question_id;
    int from_user_id;
    int to_user_id;
    int is_thread;
    int is_anony;
    char* questino_text;
    char* answer;
} question;

#include "ask.h"

void question_init(question* q,vector* splited_line);
void print_question(question* q,vector*users,vector* questions);
void update_questions(question *q);
void rewrite_question_to_data_base(vector* questions);

#endif  // QUESTION_H

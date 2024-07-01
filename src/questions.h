#ifndef QUESTION_H
#define QUESTION_H 
#include "ask.h"


typedef struct {

    int question_id;
    int from_user_id;
    int to_user_id;
    int is_thread;
    char* questino_text;
    char* answer;

} question;

void print_question(question* q);


#endif  // QUESTION_H

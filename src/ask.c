#include "ask.h"
#include "helper.h"
#include "questions.h"
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
        free(v->users[i]);
    free(v->users);
}
void empty_vec(vector* v){
    v->size = 0;
    v->capacity = CAPACITY;
}

void load_data(vector *users,
               vector *questions,
               vector *users_line,
               vector *questions_line,
               vector *splited_string)
{ 
    free_vec(users);
    free_vec(questions);
    free_vec(users_line);
    free_vec(questions_line);
    free_vec(splited_string);

    vec_init(users,CAPACITY);
    vec_init(questions,CAPACITY);
    vec_init(users_line,CAPACITY);
    vec_init(questions_line,CAPACITY);
    vec_init(splited_string,CAPACITY);

    read_from_file("databases/questions.txt",questions_line);
    read_from_file("databases/users.txt",users_line); 
    user* new_user;
    question* new_question;
    for(size_t i = 0; i < questions_line->size; ++i){
        new_question = malloc(sizeof(question)); 
        check_malloc_fail(new_question);
        split_string(questions_line->users[i],",",splited_string);                
        question_init(new_question, splited_string); 
        empty_vec(splited_string); 
        append(questions, new_question);
    }
    for(size_t i = 0; i < users_line->size; ++i){
        new_user = malloc(sizeof(user)); 
        check_malloc_fail(new_user);
        split_string(users_line->users[i],",",splited_string);         
        user_init(new_user,splited_string); 
        empty_vec(splited_string); 
        append(users,new_user);
    }

}

void print_users(vector*users)
{
    for(size_t i = 0; i < users->size; ++i)
        print_user((user*)users->users[i]);
}
void print_questions(vector* questions)
{
    for(size_t i = 0; i < questions->size;++i){
        question *q = questions->users[i];
        if(q->is_thread == -1)
            print_question(q,questions);
    }
}

int get_question_id(question *last_question)
{
   return last_question->question_id; 
}

void ask_question(user *cur_user,vector* users,vector *questions){
    int to_user_id = 0;
    question *new_question;
    printf("Enter user ID or -1 to cancel: ");
    scanf("%d",&to_user_id);
    if(to_user_id == -1)
        return;
    
    if(find_user_id(to_user_id,users) == 1)
        printf("This user allow anonymos questions.\n");
    else 
        printf("This user does not allow anonymos questinos.\n");

    new_question = malloc(sizeof(question));
    new_question->to_user_id = to_user_id; 
    printf("For thread question enter the question ID or -1 for new question: ");
    int is_thread = 0;
    scanf("%d",&is_thread);
    
    new_question->is_thread = is_thread;
    clean_buffer();
    printf("Enter question text: ");
    size_t buffer_size = 100;
    char* q_text = malloc(sizeof(char) * buffer_size);

    input(q_text, &buffer_size);

    new_question->questino_text = strdup(q_text);
    free(q_text);

    new_question->from_user_id  = cur_user->user_id;

    if(questions->size == 0)
        new_question->question_id = 1;
    else 
        new_question->question_id   = get_question_id(questions->users[questions->size-1]);

    ++new_question->question_id;
    
    new_question->answer = " ";
    update_questions(new_question); 
}
void print_question_from_me(user *cur_user,vector *questions)
{
    // TODO: get all cur_users questions in one place
}
int hase_answer(vector* questions,int *id)
{
    for(size_t i = 0; i < questions->size;++i ){
        question* q = questions->users[i];
        if(q->question_id == *id){
            *id = i;
            return (strcmp(q->answer," ") == 0) ? 0 : 1;
        }
    }
    return -1;
}


void answer_question(user *cur_user,vector *questions)
{
    int id = 0;
    printf("Enter the Question ID: ");
    scanf("%d",&id);
    int hase_ans = hase_answer(questions,&id) ; 
    question *q = questions->users[id];
    if( (size_t)q->to_user_id != cur_user->user_id && id != -1){
        printf("You only can answer questions for you!\n");
        return;
    }
    if(hase_ans == 1){
        int choice = -1;
        printf("You already answer This question!\n");
        printf("Enter 1 to edite the answer or -1 to return : ");
        scanf("%d",&choice);
        if(choice == -1)
            return;
        else {
            clean_buffer();
            size_t buffer_size = 100;
            char* answer = malloc(sizeof(char) * buffer_size);
            printf("Enter the answer text: ");
            input(answer,&buffer_size);
            question * updated = questions->users[id];
            updated->answer = strdup(answer);
            rewrite_question_to_data_base(questions); 
            free(answer);     
        }
    }
    else if(hase_ans == 0){
            clean_buffer();
            size_t buffer_size = 100;
            char* answer = malloc(sizeof(char) * buffer_size);
            printf("Enter the answer text: ");
            input(answer,&buffer_size);
            question * updated = questions->users[id];
            updated->answer = strdup(answer);  
            rewrite_question_to_data_base(questions); 
            free(answer);     
    }
    else {
        printf("Question does not exist!\n");
        return;
    }
}
void print_from(user *cur_user,vector* questions)
{
   int no_question_from_me = 1;
   for(size_t i = 0; i < questions->size;++i){
        question *q = questions->users[i];
        if(q->from_user_id == cur_user->user_id)
        {
            no_question_from_me = 0;
            print_question(q,questions);
        }
    }
    if(no_question_from_me)
        printf("You don't have any questions from you!:(\n");
}
void show_quesion_for_me(user *cur_user,vector *users,
               vector *questions,
               vector *users_line,
               vector *questions_line,
               vector *splited_string)
{
    load_data(users,questions,users_line,questions_line,splited_string);
    print_from(cur_user,questions);
}
void show_feed(vector *users,
               vector *questions,
               vector *users_line,
               vector *questions_line,
               vector *splited_string)
{
    load_data(users,questions,users_line,questions_line,splited_string);
    print_questions(questions);
}




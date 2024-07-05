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
void show_feed(vector* questions,vector* users)
{
    if(questions->size == 0){
        printf("Empty feed.\n");
        return;
    }
    for(size_t i = 0; i < questions->size;++i){
        question *q = questions->users[i];
        print_question(q,users,questions);
    }
}

int get_question_id(question *last_question)
{
   return last_question->question_id; 
}

int valid_question_id(vector *questions,int is_thread )
{
    for(size_t i=0;i<questions->size;++i){
        question *q = questions->users[i];
        if(is_thread == q->question_id)
            return 1;
    }
    return 0;
}

void ask_question(user *cur_user,vector* users,vector *questions){
    int to_user_id = 0;
    question *new_question;
    printf("\nEnter user ID or -1 to cancel: ");
    scanf("%d",&to_user_id);
    if(to_user_id == -1)
        return;
    if((size_t)to_user_id == cur_user->user_id){
        printf("\nYou can't ask yourself!:(\n");
        return;
    }
     
    int allow_anon = allow_anonymous(to_user_id,users) ; 
    if(allow_anon == 0){
        printf("\nThe ID of user Not found in the system\nTry Again!\n");
        return;
    }
    else if(allow_anon == 1){
        printf("\nThis user allow AQ!\n");
    }
    else 
        printf("\nThis user does not allow AQ!\n");

    new_question = malloc(sizeof(question));
    new_question->to_user_id = to_user_id; 
    printf("\nFor thread question enter the QuestionID or -1 for new question: ");
    int is_thread = 0;
    scanf("%d",&is_thread);
    if(!valid_question_id(questions,is_thread) && is_thread != -1)
    {
        printf("\nThe ID of question Not found in the system\nTry again!\n");
        return;
    }
    new_question->is_thread = is_thread;
    clean_buffer(); 
    
    
    if(allow_anon == 1){
        printf("\nEnter -1 for AQ! or 1 for normale Question: ");
        scanf("%d",&new_question->is_anony);
        clean_buffer();
    }
    else {
        new_question->is_anony = 1;
    }
    
    size_t buffer_size = 100; 
    char* q_text = malloc(sizeof(char) * buffer_size);
    
    printf("\nEnter question text: ");
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
    printf("\nEnter the Question ID: ");
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
        printf("\nEnter 1 to edite the answer or -1 to return : ");
        scanf("%d",&choice);
        if(choice == -1)
            return;
        else {
            clean_buffer();
            size_t buffer_size = 100;
            char* answer = malloc(sizeof(char) * buffer_size);
            printf("\nEnter the answer text: ");
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
            printf("\nEnter the answer text: ");
            input(answer,&buffer_size);
            question * updated = questions->users[id];
            updated->answer = strdup(answer);  
            rewrite_question_to_data_base(questions); 
            free(answer);     
    }
    else {
        printf("\nQuestion does not exist!\n\n");
        return;
    }
}

void print_question_from_me(user *cur_user,vector* users,vector* questions)
{
   int no_question_from_me = 1;
   for(size_t i = 0; i < questions->size;++i){
        question *q = questions->users[i];
        if((size_t)q->from_user_id == cur_user->user_id)
        {
            no_question_from_me = 0;  
            printf("QuestionID[%d]",q->question_id); 
            if(q->is_anony == -1){
                printf("AQ! ");
            }
            else{
                printf("From UserName[%s] with UserID[%d] ",get_user_name(users,q->from_user_id),q->from_user_id);
            }
            printf("To UserName[%s] with ID[%d]:\n\tQuestion:%s\tAnswer:",get_user_name(users,q->from_user_id),q->to_user_id,q->questino_text);
            if(strcmp(q->answer," ")==0)
                printf("No answer yet!\n\n");
            else
                printf("%s\n\n",q->answer);
        }
    }
    if(no_question_from_me)
        printf("You don't have any question for now!:(\n\n");

}

void print_question_to_me(user *cur_user,vector* users,vector* questions)
{
   int no_question_to_me = 1;
   for(size_t i = 0; i < questions->size;++i){
        question *q = questions->users[i];
        if((size_t)q->to_user_id == cur_user->user_id)
        {
            no_question_to_me = 0; 
            printf("QuestionID[%d]",q->question_id); 
            if(q->is_anony == -1){
                printf("AQ! ");
            }
            else{
                printf("From UserName[%s] with UserID[%d] ",get_user_name(users,q->from_user_id),q->from_user_id);
            }
            printf("To UserName[%s] with ID[%d]:\n\tQuestion:%s\tAnswer:",get_user_name(users,q->to_user_id),q->to_user_id,q->questino_text);
            if(strcmp(q->answer," ")==0)
                printf("No answer yet!\n\n");
            else
                printf("%s\n\n",q->answer);
        }
    }
    if(no_question_to_me)
        printf("You don't have any question for now!:(\n\n");

}



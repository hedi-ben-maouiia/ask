#include "questions.h"
#include "helper.h"
#include "ask.h"

void question_init(question *q, vector* splited_line)
{
    q->question_id     = to_int(splited_line->users[0]);
    q->from_user_id    = to_int(splited_line->users[1]);
    q->to_user_id      = to_int(splited_line->users[2]);
    q->is_thread       = to_int(splited_line->users[3]);
    q->is_anony        = to_int(splited_line->users[4]);
    q->questino_text   = splited_line->users[5];
    q->answer          = splited_line->users[6];    
}

void print_question(question *q,vector *users,vector *questions)
{
    char* answer = " ";
    if(strcmp(answer,q->answer)== 0)
        answer = "No answer yet!";
    else 
        answer = q->answer; 
    if(q->is_thread == -1){   
       printf("QuestionID[%d]: ",q->question_id); 
        if(q->is_anony == -1){
            printf("AQ! ");
        }
        else{
            printf("From UserName[%s] with ID[%d]: ",get_user_name(users,q->from_user_id),q->from_user_id);
        }
        printf("To UserName[%s] with ID[%d]:\n\tQuestion:%s\tAnswer:%s\n\n",get_user_name(users,q->to_user_id),q->to_user_id,q->questino_text,answer);
    } 
    for(size_t i=0;i<questions->size;++i){
        question *thread = questions->users[i];
        if(thread->is_thread == q->question_id){
           printf("\tThread!:QuestionID[%d]: ",thread->question_id); 
            if(thread->is_anony == -1){
                printf("AQ! ");
            } else{
                printf("From UserName[%s] With ID[%d]: ",get_user_name(users,thread->from_user_id),thread->from_user_id);
            }
            printf("To UserName[%s] with ID[%d]:\n\t\tQuestion:%s\tAnswer:",get_user_name(users,thread->to_user_id),thread->to_user_id,thread->questino_text);
            if(strcmp(thread->answer," ") == 0)
                printf("No answer yet!\n\n");
            else 
                printf("%s\n\n",thread->answer);
        }
    }
}

void update_questions(question *q)
{
    
    FILE* file = fopen("databases/questions.txt","a");
    if(NULL == file){
        fprintf(stderr,"Cannot open file to write\n");
        exit(1);
    }
    write_to_file(file,"%d,%d,%d,%d,%d,%s,%s,\n",q->question_id,
                                             q->from_user_id,
                                             q->to_user_id,
                                             q->is_thread,
                                             q->is_anony,
                                             q->questino_text,
                                             q->answer);
    fclose(file);

}
void rewrite_question_to_data_base(vector* questions)
{
    FILE *file = fopen("databases/questions.txt","w");
    if(NULL == file){
        fprintf(stderr,"Cannot open file to rewrite\n");
        exit(1);
    }
    for(size_t i=0; i < questions->size;++i) 
    {
        question *q = questions->users[i];
        write_to_file(file,"%d,%d,%d,%d,%d,%s,%s\n",q->question_id,
                                             q->from_user_id,
                                             q->to_user_id,
                                             q->is_thread,
                                             q->is_anony,
                                             q->questino_text,
                                             q->answer);
    }
    fclose(file);
}

#include "questions.h"
#include "helper.h"
#include "ask.h"

void question_init(question *q, vector* splited_line)
{
    q->question_id = to_int(splited_line->users[0]);
    q->from_user_id= to_int(splited_line->users[1]);
    q->to_user_id  = to_int(splited_line->users[2]);
    q->is_thread   = to_int(splited_line->users[3]);
    q->questino_text= splited_line->users[4];
    if(splited_line->users[5] == NULL)
        q->answer = "Not answred yet";
    else 
        q->answer = splited_line->users[5];
}

void print_question(question *q)
{
    char* answer = " ";
    if(strcmp(answer,q->answer)== 0)
        answer = "No answer yet!";
    else 
        answer = q->answer;
    if(q->is_thread != -1 )
        printf("\tTread: ");
    printf("QuestionID[%d]: from User ID[%d] To User ID[%d]\n\tQ:%s\t\tAnswer:%s\n",q->question_id,q->from_user_id,q->to_user_id,q->questino_text,answer);
}

void update_questions(question *q)
{
    
    FILE* file = fopen("databases/questions.txt","a");
    if(NULL == file){
        fprintf(stderr,"Cannot open file to write\n");
        exit(1);
    }
    write_to_file(file,"%d,%d,%d,%d,%s,%s\n",q->question_id,
                                             q->from_user_id,
                                             q->to_user_id,
                                             q->is_thread,
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
        write_to_file(file,"%d,%d,%d,%d,%s,%s\n",q->question_id,
                                             q->from_user_id,
                                             q->to_user_id,
                                             q->is_thread,
                                             q->questino_text,
                                             q->answer);
    }
    fclose(file);
}

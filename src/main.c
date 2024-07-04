#include "ask.h" 
#include "helper.h"
#include "users.h"
#include "questions.h"


void access_system(user* cur_user, 
                   vector* users,
                   vector* questions,
                   vector* users_line,
                   vector* questions_line,
                   vector* splited_line)
{
    load_data(users,questions,users_line,questions_line,splited_line);
    vector *menu =  malloc(sizeof(vector));
    vec_init(menu,CAPACITY);
    append(menu,"Login");
    append(menu,"SignUp");
    append(menu,"Exit");        
    int choice = 0; 
    printf("____________Welcom To ASK.FM___________\n\n"); 
        choice = show_menu(menu);
        if(choice == 1)
            login(cur_user,users,questions,users_line,questions_line,splited_line);
        else if(choice == 2)
            sign_up(cur_user,users,questions,users_line,questions_line,splited_line); 
        else if(choice == 3){
            free(menu->users);
            free(menu);
            printf("Bye...!\n"); 
            exit(0);
        }
    free(menu->users);
    free(menu);
}

void ask_system(user* cur_user, 
                   vector* users,
                   vector* questions,
                   vector* users_line, 
                   vector* questions_line,
                   vector* splited_line)
{
    vector *menu = malloc(sizeof(vector));
    vec_init(menu,CAPACITY);
    
    access_system(cur_user,users,questions,users_line,questions_line,splited_line);
   
    
    append(menu,"View Question To You");
    append(menu,"View Question From You");
    append(menu,"Ask a Question");
    append(menu,"Answer a Question");
    append(menu,"Delete a Question");
    append(menu,"View All Users");
    append(menu,"Show Feed");
    append(menu,"Logout.");
    int exit = 0;
    while(!exit){
        int choice = 0;
        choice = show_menu(menu);
        switch(choice){
            case 1:
                break;
            case 2:
                show_quesion_for_me(cur_user, users,questions,users_line,questions_line,splited_line);
                break;
            case 3:
                ask_question(cur_user,users,questions);
                break;
            case 4:
                answer_question(cur_user,questions);
                break;
            case 5:
                
            case 6:
                print_users(users);
                break;
            case 7:
                show_feed(users,questions, users_line, questions_line, splited_line); 
                break;
            case 8:
                ask_system(cur_user, users, questions,users_line,questions_line,splited_line);
        }
    }

    free(menu->users);
    free(menu);
}


int main(void)
{ 
    
    vector *users           = malloc(sizeof(vector));
    vector *questions       = malloc(sizeof(vector)); 
    vector *users_line      = malloc(sizeof(vector));
    vector *questions_line  = malloc(sizeof(vector));
    vector *splited_line    = malloc(sizeof(vector));; 
    
    user *cur_user          = malloc(sizeof(user));
    
    vec_init(users,CAPACITY);
    vec_init(questions,CAPACITY);
    vec_init(users_line,CAPACITY);
    vec_init(questions_line,CAPACITY);
    vec_init(splited_line,CAPACITY);

    
    ask_system(cur_user,users,questions,users_line,questions_line,splited_line); 
    
    free_vec(users);
    free_vec(questions);
    free_vec(users_line);
    free_vec(questions_line);
    free_vec(splited_line);

    free(cur_user);
    free(users);
    free(questions);
    free(users_line);
    free(questions_line);
    free(splited_line);
    return 0;
}

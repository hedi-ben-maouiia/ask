#include "ask.h" 
#include "helper.h"
#include "users.h"



void access_system(user* cur_user, 
                   vector* users,
                   vector* lines,
                   vector* splited_line)
{
    load_users(users,lines,splited_line);
    vector *menu =  malloc(sizeof(vector));
    vec_init(menu,CAPACITY);
    append(menu,"Login");
    append(menu,"SignUp");
    append(menu,"Exit");        
    int choice = 0; 
    printf("____________Welcom To ASK.FM___________\n\n"); 
        choice = show_menu(menu);
        if(choice == 1)
            login(cur_user,users,lines,splited_line);
        else if(choice == 2)
            sign_up(cur_user,users,lines,splited_line); 
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
                   vector* lines,
                   vector* splited_line)
{
    vector *menu = malloc(sizeof(vector));
    vec_init(menu,CAPACITY);
    
    access_system(cur_user,users,lines,splited_line);
    
    append(menu,"View Question To You!");
    append(menu,"View Question From You!");
    append(menu,"View All Users");
    append(menu,"Show Feed");
    append(menu,"Logout."); 
    int choice = 0;
    while(1){
        choice = show_menu(menu);
        switch(choice){
            case 1:
                break;
            case 2:
                break;
            case 3:
                print_users(users);
                break;
            case 4:
                break;
            case 5:
                break;
        }
        break;
    }
    free(menu->users);
    free(menu);
}


int main(void)
{ 
    
    vector *users = malloc(sizeof(vector));
    vector *lines = malloc(sizeof(vector));
    vector *splited_line = malloc(sizeof(vector));; 
    user *cur_user = malloc(sizeof(user));

    vec_init(users,CAPACITY);
    vec_init(lines,CAPACITY);
    vec_init(splited_line,CAPACITY);

    
    ask_system(cur_user,users,lines,splited_line); 
    
    free_vec(users);
    free_vec(lines);
    free_vec(splited_line);
    free(cur_user);
    free(users);
    free(lines);
    free(splited_line);
    return 0;
}

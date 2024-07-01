#include "ask.h" 
#include "helper.h"
#include "users.h"



void access_system(user* cur_user, 
                   vector* users,
                   vector* lines,
                   vector* splited_line )
{
    vector v;
    vec_init(&v,CAPACITY);
    append(&v,"Login");
    append(&v,"SignUp");
    append(&v,"Exit");

    
    int choice = 0; 
    printf("____________Welcom To ASK.FM___________\n\n");
        load_users(users,lines,splited_line); 
        choice = show_menu(&v);
        if(choice == 1)
            login(cur_user,users);
        else if(choice == 2)
            sign_up(cur_user,users,splited_line); 
        else {
            printf("Bye...!\n"); 
            exit(0);
        }
}
void ask_system(user* cur_user, 
                   vector* users,
                   vector* lines,
                   vector* splited_line)
{
    vector menu;
    vec_init(&menu,CAPACITY);
    
    access_system(cur_user,users,lines,splited_line);
    
    append(&menu,"View Question To You!");
    append(&menu,"View Question From You!");
    append(&menu,"View All Users");
    append(&menu,"Show Feed");
    append(&menu,"Logout."); 
    int choice = 0;
    while(1){
        choice = show_menu(&menu);
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
}

int main(void)
{ 
    
    vector users,lines,splited_line; 
    user* cur_user = malloc(sizeof(user));

    vec_init(&users,CAPACITY);
    vec_init(&lines,CAPACITY);
    vec_init(&splited_line,CAPACITY);

    
    ask_system(cur_user,&users,&lines,&splited_line); 

    free_vec(&users);
    free_vec(&lines);
    free_vec(&splited_line);
    free(cur_user);

    return 0;
}

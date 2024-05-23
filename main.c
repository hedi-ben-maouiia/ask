#include<stdio.h>
#include<string.h>
#include "lib/vector.h"

/*============== HELPER FUNCTIONS =================*/
void readfile(const char* path,vector* v, int length){ 
    FILE* file;
    file = fopen(path,"r");
    if(file == NULL){
        perror("ERROR: opening file");
        return; 
    }
    static char str[100]; 
    while(fgets(str,100,file)){
        push_back(v,str); 
    }
    fclose(file);
}

int find(char *str ,const char delim){
    int count = 0; 
 
    while(*str){
        if(*str == delim){  
            return count; 
        }
        *str = '\0';
        count++;
        ++str;
    } 
    return -1;
}

void split_string(char *s,vector * v, char *delim){     

}

int print_menu(vector* v){ 
    int choice = 0; 
    printf("\t\tMenu:\n");
    for(int i=0;i<v->size;++i){
        printf("\t\t%d) %s\n", i+1,(char*)v->items[i]); 
    }
    printf("Enter a choice between 1 and %d: ",v->size); 
    scanf("%d",&choice);     
    return choice;
}

/*============== HELPER FUNCTIONS =================*/

enum {
    LOGIN, 
    SIGN_UP,
};



typedef struct{
    size_t user_id;
    char*  user_name;
    char*  user_email;
    char*  password;
    int    is_ananymose;
} usersManager;

usersManager users = {0};

typedef struct  {  
    
    size_t quition_id;      // quition id itself 
    size_t quition_from_id; // quitions id from the user {user_name}
    size_t quition_to_id;   // the id of the user {user_name} 
    char*  quition;
    char*  answer;

} quitionsManager;


typedef struct{ 
    usersManager *users;
    quitionsManager *quitions;

} askSystem;


void runSystem(){
    vector menu;
    vector_init(&menu);
    push_back(&menu, "Login.");
    push_back(&menu, "SignUp."); 
    int choice = print_menu(&menu);
    while(0 <= choice && choice > 2){
        printf("Pleas enter a valid choice between 1 and %d: ",menu.size);
        scanf("%d", &choice);
    }
    if(choice == LOGIN){
        vector_free(&menu);
        push_back(&menu,"Enter UserName: ");
        push_back(&menu,"Enter Password:");
        //login(&menu,); 
    }
    else if(choice == SIGN_UP){
        //sign_up();    
    }
    else {

    }
}
int main(){

    
    return 0;
}

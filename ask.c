#include "lib/ask.h"


void read_from_file(const char* path,vector* v){ 
    FILE *file =  fopen(path,"r");
    if(file == NULL){
        perror("ERROR: opening file");
        return; 
    }

    char buffer[LINE_BUFFER_SIZE];

    while(fgets(buffer,LINE_BUFFER_SIZE,file)){
        buffer[strcspn(buffer,"\n")] = '\0'; 
        push_back(v,buffer);
    }
     
    fclose(file);

}
void write_to_file(const char* path, vector* v, bool apend){
    char * ap;
    if(apend)
        ap = "a";
    else 
        ap = "w";
    
    FILE* file = fopen(path,ap);
    if(NULL == file){
        printf("ERROR: can't open file for writing\n");
        return;
    }
    for(int i=0;i<v->size;++i) 
        fputs(v->items[i], file),fputc('\n',file);

    fclose(file);
    
}

void split_string(char *str,vector * v,const char delim){     
    char buffer[100];
    int j=0;
    for(int i=0;str[i] != '\0';++i){
        buffer[j++] = str[i]; 
        if(str[i] == delim){
            buffer[j-1] = '\0';
            push_back(v,buffer);
            j=0;
        }    
    }
    buffer[j] = '\0';
    push_back(v,buffer);
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

void user_init(user_info* u, char* str){
    
    //TODO: not complete 
    (void) u; 
    vector line;
    vector_init(&line);
    split_string(str,&line,',');

}

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
    if(choice == 0){
        vector_free(&menu);
        push_back(&menu,"Enter UserName: ");
        push_back(&menu,"Enter Password:");
        //login(&menu,); 
    }
    else if(choice == 1){
        //sign_up();    
    }
    else {

    }
}

#include "lib/ask.h"
#include "lib/vector.h"
#include <stdbool.h>

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

int to_int(char* str){ 
    int is_negative = 1; 
    int ret = 0; 
    int number = 0;
    
    while(*str){
        if( *str == '-'){
            is_negative = -1;
            str++;
            continue; 
        } 
        number = (int) *str;
        number &= 0x0f;
        ret = (ret +  number)  * 10; 
        str++; 
    }
    return (is_negative < 0) ? -(ret/10) : (ret/10);
}
char* to_str(int n){
    bool is_negative = false;
    if(n<0){
        is_negative = true;
        n *= -1;
    }
    char* ret; 
    int  rem = 0;  
    int  len = 0;
    int  num = n;
    while(n){ len++,n/= 10; }
     
    char* buffer = (char*) malloc(len+1);
    if(is_negative){
        buffer[0] = '-';
        len++;
    } 
    for(int i = 0;i<len;++i){
         
        if(is_negative && ((len - (i+1)) == 0)){
            break;
        }         
        rem = num % 10;
        num /= 10; 
        buffer[len - (i + 1)] = rem + '0';  

    }
    buffer[len] = '\0';
        
    ret = strdup(buffer);
     
    free(buffer);
    return ret;
}
char* user_to_string(user_info* user){
    vector v;
    vector_init(&v);
    push_back(&v,to_str(user->user_id));
    push_back(&v,",");
    push_back(&v,user->name);
    push_back(&v,",");
    push_back(&v,user->user_name);
    push_back(&v,",");
    push_back(&v,user->user_email);
    push_back(&v,",");
    push_back(&v,user->password);
    push_back(&v,",");
    push_back(&v,to_str(user->is_ananymose));
    
    static char buffer[256]; 
    char* prefix = buffer;
 
    for(int i = 0; i < get_size(&v);i++){
        prefix = strcat(prefix,v.items[i]); 
    }
    vector_free(&v);
    return prefix;
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

void sign_up(user_info* user){
    vector users;
    vector_init(&users);

    printf("Enter your user_name: ");
    scanf("%s", user->user_name);
    printf("\nEnter your name: ");
    scanf("%s", user->name);
    printf("\nEnter your email: "); 
    scanf("%s", user->user_email);
    printf("\nEnter your passsword: "); 
    scanf("%s",user->password);
    printf("\nDo you allow ananymose Quitions enter 1 or -1 for (y/n): ");
    scanf("%d", &user->is_ananymose);
 
    user->user_id = ++USER_ID;
     
    push_back(&users,user_to_string(user));
    write_to_file("users.txt",&users,true); 
    vector_free(&users);
}
user_info* user(user_info* new_user){
    
    new_user->name          = (char*) malloc(50);
    new_user->user_name     = (char*) malloc(50);
    new_user->user_email    = (char*) malloc(50);
    new_user->password      = (char*) malloc(50);
    new_user->is_ananymose  = -1;
    new_user->user_id       = 0; 
    return new_user;
}
void user_init(user_info* u, char* str){  
    vector users; 
    vector_init(&users);
    split_string(str,&users,',');
    
    u->user_id      = to_int(strdup(users.items[0]));
    u->name         = strdup(users.items[1]); 
    u->user_name    = strdup(users.items[2]);
    u->password     = strdup(users.items[3]);
    u->user_email   = strdup(users.items[4]);
    u->is_ananymose = to_int(strdup(users.items[5]));
     
    vector_free(&users);    
}

void user_free(user_info* user){
    free(user->name);
    free(user->password);
    free(user->user_name);
    free(user->user_email);
}
void quistion_init(quistion_info *q, char *str){
    vector quistions;
    vector_init(&quistions);
    split_string(str,&quistions,',');

    q->quition_id       = to_int(strdup(quistions.items[0]));
    q->quition_from_id  = to_int(strdup(quistions.items[1]));
    q->quition_to_id    = to_int(strdup(quistions.items[2]));
    q->quition          = strdup(quistions.items[3]);
    q->answer           = strdup(quistions.items[4]);

    vector_free(&quistions);
}

void run_system(void){
    vector menu;
    vector_init(&menu);
    push_back(&menu, "Login.");
    push_back(&menu, "SignUp."); 
    int choice = print_menu(&menu);
    
    while(0 <= choice && choice > 2){
        printf("Pleas enter a valid choice between 1 and %d: ",menu.size);
        scanf("%d", &choice);
    }

    while(true){
        switch (choice) {
            case 1: 
                break;
            case 2:
                user_info new_user;
                user(&new_user);
                sign_up(&new_user);
                user_free(&new_user); 
                break; 
                
        }
        break;

    }
}


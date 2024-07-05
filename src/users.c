#include "ask.h"
#include "helper.h"
#include <stdlib.h>


int loaded(vector* users){
    return (users->size > 0) ? 1 : 0;
}

void clean_buffer(void)
{
    int c ;
    while((c = getchar()) != '\n' && c != EOF){}
}
void check_get_line(int a,void* p)
{
    if(a == -1){
        fprintf(stderr, "Error reading input\n");
        free(p);
        exit(1);
    }
}
void input(char* data,size_t *size)
{
    int c;
    c = getline(&data,size,stdin);
    data[strlen(data)-1] = '\0'; 
    check_get_line(c,data);
}

int get_id(user* last_user){
    int id = last_user->user_id;
    return id;
}
void sign_up(user* cur_user, vector *users, 
             vector *questions, 
             vector *users_line,
             vector *questions_line,
             vector* splited_string)
{ 
    int id;
    size_t buffer_size = 50;
    char* is_an    = malloc(sizeof(char) * buffer_size);
    char* name     = malloc(sizeof(char) * buffer_size);
    char* username = malloc(sizeof(char) * buffer_size);
    char* pass     = malloc(sizeof(char) * buffer_size);
    char* email    = malloc(sizeof(char) * buffer_size);

    clean_buffer();
      
    printf("Enter your name: ");
    input(name,&buffer_size); 
    printf("\nEnter your user_name: "); 
    input(username,&buffer_size); 
    while(!used_user_name(username,users)){
        username = NULL;
        printf("This user_name is already taken! Try another one\n");
        input(username,&buffer_size); 
    } 
    printf("\nEnter your email: ");
    input(email,&buffer_size);
    printf("\nEnter your password: "); 
    input(pass,&buffer_size);
    printf("\nDo you allow AQ!: enter 1 for yes or -1 for no: "); 
    input(is_an,&buffer_size);

    if(users->size == 0)
        id = 0;
    else 
        id = get_id(users->users[users->size-1]);
    ++id; 
    
    append(splited_string, to_str(&id)); 
    append(splited_string, strdup(is_an)); 
    append(splited_string, strdup(username)); 
    append(splited_string, strdup(name)); 
    append(splited_string, strdup(email)); 
    append(splited_string, strdup(pass));  

    user_init(cur_user, splited_string);    
    
    update_users(cur_user); 
    load_data(users,questions,questions_line,users_line,splited_string); 

    free(is_an); 
    free(username);
    free(name);
    free(email);
    free(pass);
}
int allow_anonymous(int id,vector *users)
{
    for(size_t i = 0; i < users->size;++i){
        user* cur_user = users->users[i];
        if(cur_user->user_id == (size_t)id)
            return cur_user->is_anonymous;
    }
    return 0;
}
int user_exist(const char* user_name, const char* pass,vector* users,user *cur)
{
    for(size_t i=0;i < users->size;++i){
        user* cur_user = users->users[i];
        if(strcmp(user_name,cur_user->user_name) == 0){
            if(strcmp(pass,cur_user->password) == 0){
                *cur = *cur_user;
                return 1;
            }
        }
    }
    return 0;
}
void login(user* cur_user,
           vector* users,
           vector* questions,
           vector* users_line,
           vector* questions_line,
           vector* splited_string)
{
    load_data(users,questions,users_line,questions_line,splited_string);
    size_t buffersize = 50;
    char user_name[buffersize];
    char pass[buffersize];
    clean_buffer();
    printf("Enter you user_name: ");
    input(user_name,&buffersize);
    printf("Enter you password: ");    
    input(pass,&buffersize); 
       
    if(!user_exist(user_name,pass, users, cur_user)){
        printf("Wrong user_name or password! pleas try again\n");
        login(cur_user,users,questions,users_line,questions_line,splited_string);
    }    
}

int used_user_name(char* u,vector*users)
{
    int ret = 1;
    for(size_t i=0; i < users->size;++i){
        user* cur_user = users->users[i];
        ret = strcmp(cur_user->user_name,u);
        if(ret == 0)
            return ret;
    }
    return ret;
}

void update_users(user* user){
    FILE* file = fopen("databases/users.txt","a");
    if(NULL == file){
        fprintf(stderr,"Cannot open file to write\n");
        exit(1);
    }
    write_to_file(file,"%d,%d,%s,%s,%s,%s\n",user->user_id,
                                             user->is_anonymous,
                                             user->user_name,
                                             user->name,
                                             user->email,
                                             user->password);
    fclose(file);
}
void user_init(user* user, vector *v)
{
    user->user_id      = to_int((char*)v->users[0]);
    user->is_anonymous = to_int((char*)v->users[1]);
    user->user_name    = (char*)v->users[2];  
    user->name         = (char*)v->users[3];  
    user->email        = (char*)v->users[4];
    user->password     = (char*)v->users[5];  
}

void print_user(user *user)
{
    printf("User ID[%zu]\tUser Name:%20s\tEmail:%20s\tName: %s\tAQ!: ", user->user_id, user->user_name,user->email,user->name);
    if(user->is_anonymous == -1)
         printf("No");
    else 
        printf("Yes");
    printf("\n");
}

size_t  get_user_id(user *user)
{
    return user->user_id;
}

char*   get_user_name(vector *users,int id)
{
    size_t cpy = id;
    for(size_t i =0; i < users->size;++i){
        user* u = users->users[i];
        if(cpy == u->user_id)
            return strdup(u->name);
    }
    return NULL;
}

char*   get_user_pass(user *user)
{
    return user->password;
}




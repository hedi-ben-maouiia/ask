#include "lib/ask.h"
#include "lib/vector.h"



int main(void){
    vector lines, split_vec; 
    vector_init(&split_vec);
    vector_init(&lines);

    read_from_file("users.txt",&lines);
    split_string(lines.items[0],&split_vec,',');
    write_to_file("quitions.txt",&split_vec,true);

    print_vector(&lines);
    print_vector(&split_vec);

    vector_free(&lines);
    vector_free(&split_vec);

}

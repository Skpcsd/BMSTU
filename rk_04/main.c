#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main() 
{
    list_t *list = process_file("in.txt");
    if (list == NULL) 
        return 1;
    print_to_file(list, "out.txt");
    free_list(list);
    return 0;
}


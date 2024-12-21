#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 1000
typedef struct node 
{
    char *data;
    struct node *next;
} node_t;

typedef struct list 
{
    node_t *head;
} list_t;

char *my_strdup(const char *s);
list_t *process_file(const char *filename);
void free_list(list_t *list);
void print_to_file(list_t *list, const char *filename);
node_t* add_node(node_t* head, char* data);


#endif


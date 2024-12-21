#define _POSIX_C_SOURCE 200809L

#include "list.h"

char *my_strdup(const char *s)
{
    char *d = malloc(strlen(s) + 1);

    if (d)
        strcpy(d, s);

    return d;
}

int add_node_to_end(list_t *list, const char *data)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) return 0;

    new_node->data = my_strdup(data);

    if (new_node->data == NULL) 
    {
        free(new_node);
        return 0;
    }
    new_node->next = NULL;

    if (list->head == NULL) 
        list->head = new_node;
    else 
    {
        node_t *current = list->head;
        while (current->next != NULL) 
            current = current->next;
        current->next = new_node;
    }
    return 1;
}

list_t *process_file(const char *filename) 
{
    list_t *list = (list_t *)malloc(sizeof(list_t));
    if (list == NULL) return NULL;
    list->head = NULL;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) 
    {
        free(list);
        return NULL;
    }

    char line[MAX_STR_LEN];
    while (fgets(line, sizeof(line), fp) != NULL) 
    {
        line[strcspn(line, "\n")] = 0;
        if (!add_node_to_end(list, line)) 
        {
            fclose(fp);
            free_list(list);
            return NULL;
        }
    }

    fclose(fp);
    return list;
}

void print_to_file(list_t *list, const char *filename) 
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return;

    node_t *current = list->head;
    while (current != NULL) 
    {
        const char *line = current->data;

        if (strchr(line, ' ') == NULL)
            for (size_t i = 0; i < strlen(line); i++) 
                fprintf(fp, "%c\n", line[i]);
        else 
        {
            char *copy = my_strdup(line);
            if (copy == NULL) 
            {
                fclose(fp);
                return;
            }

            char *token, *rest = copy;
            while ((token = strtok_r(rest, " ", &rest)) != NULL) 
            {
                fprintf(fp, "%s\n", token);
            }

            free(copy);
        }

        current = current->next;
    }

    fclose(fp);
}

void free_list(list_t *list) 
{
    node_t *current = list->head;
    while (current != NULL) 
    {
        node_t *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

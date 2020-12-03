#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxLength 5-

typedef struct
{
        char* string;
        struct List* next;
}List;

List* createList()
{
        List* list = (List*)malloc(sizeof(List));
        if (list == NULL)
                return list;

        list->string = NULL;
        list->next = NULL;
        return list;
}
int append(char* string, List** list)
{
        if(*list == NULL)
        {
                *list = createList();
                if(*list == NULL)
                        return -1;
                (*list)->string = string;
        }
        else
        {
                List* cur = *list;
                while (cur->next != NULL)
                {
                        cur = (List*)cur->next;
                }
                List* newIt = createList();
                if (newIt == NULL)
                        return -1;

                newIt->string = string;
                cur->next = (struct List*)newIt;
        }
        return 0;

}
void freeall(List* list)
{
        List* current = list;
        while (current != NULL)
        {
                if (current->string != NULL)
                        free(current->string);
                List* prev = current;
                current = (List*)current->next;
                free(prev);
        }
}
int main()
{
        char text[maxLength];

        List* list = NULL;

        printf("Type words\n");
        while (*(fgets(text, maxLength, stdin)) != '.')
        {
                size_t length = strlen(text);
                length += text[length-1] != '\n';

                char* t = (char*)malloc(length);
                if (t != NULL)
                {
                        memcpy(t, text, length);
                        t[length-1] = 0;
                        if(append(t, &list)!=0)
                        {
                                printf("Failed\n");
                                freeall(list);
                                return 1;
                        }
                }
                else
                {
                  freeall(list);
                  return 1;
                }
        }

        List* current = list;
        while(current != NULL)
        {
                printf("%s\n", (char*)current->string);
                current = (List*)current->next;
        }
        freeall(list);

        return 1;
}


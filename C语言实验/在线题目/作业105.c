#include <stdio.h>
int main(void)
{
    struct chars {
        char c;
        struct chars *next;
    };
    struct chars * head = NULL;
    struct chars * prev, *current;
    struct chars charss;
    char temp;
    int sum = 0, count = 0;
    while((temp = getchar()) != '#')
    {
        current = (struct chars *) malloc(sizeof(struct chars));
        if (head == NULL)
            head = current;
        else
            prev->next = current;
        current->next = NULL;
        current->c = temp;
        prev = current;
        sum++;
    }
    char *c2 = (char *) malloc((sum+1) * sizeof(char));

    current = head;
    while(current != NULL)
    {
        printf("%c", current->c);
        *(c2+count) = current->c;
        current = current->next;
        count++;
    }
    *(c2+count) = '\0';
    printf("\n\n");
    printf("%s\n", c2);
    return 0;
}

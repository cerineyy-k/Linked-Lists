#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Element {
    char word[20];
    struct Element *next;
    struct Element *prev;
} Element;

// ------------------- Define Biderectoional list --------------------
typedef struct {
    Element *Head;
    Element *Tail;
} ListBD;


// ------------------- Create Biderectoional list --------------------
ListBD CreatBD()
{
    ListBD L;
    L.Head = NULL;
    L.Tail = NULL;

    Element *p;
    char w[20];

    printf("Enter words (\"stop\" to finish):\n");

    while (1)
    {
        scanf("%s", w);

        p = malloc(sizeof(Element));
        strcpy(p->word, w);  
        p->prev = NULL;
        p->next = NULL;

        if (L.Head == NULL)      // first word
        {
            L.Head = p;
            L.Tail = p;
        }
        else                     // append at tail
        {
            L.Tail->next = p;
            p->prev = L.Tail;
            L.Tail = p;
        }

        if (strcmp(w, "stop") == 0)
            return L;
    }
}


// ------------------- Display both directions --------------------
void Display(ListBD L)
{
    Element *p;

    p = L.Head;
    printf("From the beginning:\n");

    while (p != NULL)
    {
        printf("%s", p->word);
        if (p->next != NULL) printf(" ---> ");
        p = p->next;
    }
    printf("\n");

    p = L.Tail;
    printf("From the end:\n");

    while (p != NULL)
    {
        printf("%s", p->word);
        if (p->prev != NULL) printf(" ---> ");
        p = p->prev;
    }
    printf("\n");
}


// ------------------- Delete last occurence of word --------------------
void Suppr(ListBD *L, char W[])
{
    Element *p = L->Tail;

    // Look from the end (last occurrence)
    while (p != NULL && strcmp(p->word, W) != 0)
        p = p->prev;

    if (p == NULL)
    {
        printf("Word \"%s\" not found.\n", W);
        return;
    }

    // CASE 1: Only one element
    if (L->Head == L->Tail)
    {
        L->Head = NULL;
        L->Tail = NULL;
        free(p);
        return;
    }

    // CASE 2: Remove Head
    if (p == L->Head)
    {
        L->Head = L->Head->next;
        L->Head->prev = NULL;
        free(p);
        return;
    }

    // CASE 3: Remove Tail
    if (p == L->Tail)
    {
        L->Tail = L->Tail->prev;
        L->Tail->next = NULL;
        free(p);
        return;
    }

    // CASE 4: Middle deletion
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
}

int main()
{
    ListBD L;
    char W[20];

    printf("=== Create Bidirectional List ===\n");
    L = CreatBD();

    Display(L);

    printf("\nEnter a word to delete (last occurrence): ");
    scanf("%s", W);

    Suppr(&L, W);

    printf("\nList after deletion:\n");
    Display(L);

    return 0;
}

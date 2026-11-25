#include <stdio.h>
#include <stdlib.h>

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// typedef List *Element;
// typedef struct Element = {int info ; struct Element *next;}


// typedef struct Element
// {
//     int info;
//     struct Element *next;
// } *List;

// Element *L1;
// List L1;

typedef struct Element
{
    int info;
    struct Element *next;
} Element;

Element *L;

// // ===================================
// struct Element {
//     int info;
//     struct Element *next;
// };

// struct Element *L;


Element *CreatFIFO(int n)
{
    if (n <= 0)
        return NULL;

    Element *L, *p, *q;
    int i, x;

    L = malloc(sizeof(Element));
    if (L == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    printf("give the first value ");
    scanf("%d", &x);
    L->info = x;

    q = L;

    for (i = 2; i <= n; i++)
    {
        p = malloc(sizeof(Element));
        printf("give the %dth value ", i);
        scanf("%d", &x);
        p->info = x;
        q->next = p;
        q = p;
    }
    q->next = NULL;
    return L;
}

Element *CreatLIFO(int n)
{
    Element *L, *p;
    int i, x;
    L = NULL;
    for (i = 1; i <= n; i++)
    {
        p = malloc(sizeof(Element));
        printf("give a value ");
        scanf("%d", &x);
        p->info = x;
        p->next = L;
        L = p;
    }
    return L;
}

// --->
void Display(Element *L)
{
    Element *p;
    p = L;
    while (p != NULL)
    {
        printf("---> %d ", p->info);
        p = p->next;
    }
}

int main()
{
    Element *LFIFO, *LLIFO;
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("\nCreating FIFO list...\n");
    LFIFO = CreatFIFO(n);

    printf("\nCreating LIFO list...\n");
    LLIFO = CreatLIFO(n);

    printf("\nFIFO list content:\n");
    Display(LFIFO);

    printf("\nLIFO list content:\n");
    Display(LLIFO);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
    int info;
    struct Element *next;
} Element;


Element* CreatCir()
{
    Element *L, *p, *q;
    int x;

    printf("Enter values (negative value to stop): ");
    scanf("%d", &x);

    if (x < 0)
        return NULL;

    // Create the first node
    L = malloc(sizeof(Element));
    L->info = x;
    L->next = L;  // head points to itself to keep the list always circular
    q = L;

    // Continue reading values
    while (1)
    {
        scanf("%d", &x);
        if (x < 0)
        {
            q->next = L;  // complete the circular link
            return L;
        }

        p = malloc(sizeof(Element));
        p->info = x;   // set info
        p->next = L;   // new node points to head to keep the list always circular
        q->next = p;   // previous last points to new
        q = p;         // update last
    }
}

void Display(Element *L)
{
    if (L == NULL)
    {
        printf("List is empty\n");
        return;
    }

    Element *p;
    p = L;

    printf("head ---> %d ", p->info);
    p = p->next;

    while (p != L)
    {
        printf("---> %d ", p->info);
        p = p->next;
    }

    printf(" (back to head)\n");
}


Element* Insert(Element *L, int x, int pos)
{
    Element *p, *newElem;
    int i;

    newElem = malloc(sizeof(Element));
    newElem->info = x;

    if (L == NULL)      // empty list → new circular list
    {
        newElem->next = newElem;
        return newElem;
    }

    
    p = L;

    // Insert at head (pos == 1)
    if (pos == 1)
    {
        newElem->next = L;    // new points to old head

        while (p->next != L) // go to last node
            p = p->next;

        p->next = newElem;    // last links to new
        return newElem;       // new becomes head
    }

    // Insert at position > 1
    for (i = 1; i < pos-1 && p->next != L; i++)
        p = p->next;

    newElem->next = p->next;
    p->next = newElem;

    return L;
}

int main()
{
    Element *L = NULL;
    int x, pos, choice;

    printf("=== Create Circular List ===\n");
    L = CreatCir();

    printf("List created:\n");
    Display(L);


    while (1)
    {
        printf("\n=== MENU ===\n");
        printf("1. Insert a value at a position\n");
        printf("2. Display list\n");
        printf("0. Exit\n");

        printf("\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value and position: ");
            scanf("%d %d", &x, &pos);
            L = Insert(L, x, pos);
            printf("List after insertion:\n");
            Display(L);
            break;

        case 2:
            Display(L);
            break;

        case 0:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }

}

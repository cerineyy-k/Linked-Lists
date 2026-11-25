#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
    int info;
    struct Element *next;
} Element;


// ------------------- Create FIFO --------------------
Element *CreatFIFO(int n)
{
    if (n <= 0)
        return NULL;

    Element *L, *p, *q;
    int i, x;

    L = malloc(sizeof(Element));
    if(L == NULL)
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


// // ------------------- Create LIFO --------------------
// Element *CreatLIFO (int n)
// {
//     Element *L, *p; int i, x ;
//     L = NULL;
//     for (i = 1 ; i<=n ; i++)
//     { 
//         p = malloc (sizeof(Element));
//         if (p == NULL)
//         {
//             printf("Memory allocation failed!\n");
//             exit(1);
//         }
//         printf ("give a value ");
//         scanf ("%d", &x); 
//         p->info = x; 
//         p->next = L; 
//         L = p;
//     }
//     return L;
// }

// ------------------- Display the list --------------------
void Display(Element *L)
{
    Element *p;
    p = L;
    while (p != NULL)
    {
        printf("---> %d ", p->info);
        p = p->next;
    }
    printf("\n");
}


// ------------------- Find and return address first occurrence --------------------
Element *Address_val(Element *L, int val)
{
    Element *p;
    p = L;

    while(p != NULL){ // false when p = NULL
        if(p->info == val)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// ------------------- number of occurences of a value --------------------
int number_occurences(Element *L, int val)
{
    Element *p;
    int count = 0;
    p = L;

    while(p != NULL){ // false when p = NULL
        if(p->info == val)
        {
            count++;
        }
        p = p->next;
    }

    return count;
}



// ------------------- Insert x before first y --------------------
Element *Insert_before(Element *L, int x, int y)
{
    Element *p, *prev, *newElem;

    if(L->info == y)
    {
        newElem = malloc(sizeof(Element));
        newElem->info = x;
        newElem->next = L;
        L = newElem;
        return L;
    }

    p = L;
    while(p != NULL)
    {
        // if(p->info == y)
        // {
        //     newElem = malloc(sizeof(Element));
        //     newElem->info = x;
        //     newElem->next = p;
        //     prev->next = newElem;
        //     return L;
        // }
        // prev = p;
        // OR
        if(p->next == Address_val(L, y))
        {
            newElem = malloc(sizeof(Element));
            newElem->info = x;
            newElem->next = p->next;
            p->next = newElem;
            return L;
        }
        p = p->next;
    }
    return L;
}




// ------------------- Replace even values with zero --------------------
void even_zero(Element *L)
{
    Element *p;

    p = L;
    while(p != NULL){ // false when p = NULL
        if(p->info % 2 == 0)
        {
            p->info = 0;
        }
        p = p->next;
    }
}





// ------------------- Delete all occurences --------------------
Element *Delete_occurences(Element *L, int x)
{
    Element *p, *prev;
    int cpt = 0;

    while(L->info == x && L != NULL) 
    {
        p = L;
        L = L->next;
        free(p);
    }

    p = L;

    
    while(p != NULL){ 
        if(p->info == x)
        {
            // delete 
            prev->next = p->next;
            free(p);
            p = prev;
        }
        prev = p;
        p = p->next;
    }

    return L;

}

// the 7th question in exercise 2 could mean delete all the occurences of x (which is implemented above) or it could mean only delete the duplicates and leave the first occurence of x (which is implemented bellow)

// ------------------- Delete duplicates leave first  --------------------
void Delete_repetition_leave_first(Element *L, int x)
{
    Element *p, *prev;
    int cpt = 0;

    p = L;
    while(p != NULL && p->info != x){ 
        prev = p;
        p = p->next;
    }

    p = p->next;

    while(p != NULL){ 
        if(p->info == x)
        {
            // delete 
            prev->next = p->next;
            free(p);
            p = prev;
        }

        prev = p;
        p = p->next;
    }

}




int main()
{
    Element *L;
    int n, val, x, y, num, option;

    printf("Enter the number of elements in the list: ");
    scanf("%d", &n);

    L = CreatFIFO(n);

    printf("The created list is:\n");
    Display(L);
    printf("=============================\n");

    do{
        getchar(); // wait for user
        printf("\n===== MENU =====\n");
        printf("Choose an operation to perform on the list:\n");
        printf("1. Search for a value\n");
        printf("2. return the number of occurences of value\n");
        printf("3. Insert a value before another value\n");
        printf("4. Set all even values to zero\n");
        printf("5. Delete all repetitions\n");
        printf("0. Exit\n");
        scanf("%d", &option);


        switch (option)
        {
        case 1:
            printf("Enter a value to search in the list: ");
            scanf("%d", &val);
            Element *found = Address_val(L, val);
            if (found != NULL)
                printf("Value %d found at address: %p\n", val, (void*)found);
            else
                printf("Value %d not found in the list.\n", val);
            break;
        case 2:
            printf("Enter value x: ");
            scanf("%d", &x);
            num = number_occurences(L, x);
            printf("number of occurences of %d is: %d times\n", x, num);

        case 3:
            printf("Enter value x: ");
            scanf("%d", &x);
            printf("Insert before value y: ");
            scanf("%d", &y);
            L = Insert_before(L, x, y);
            printf("List after insertion:\n");
            Display(L);
            printf("\n");
            break;
        case 4:
            even_zero(L);
            printf("List after setting even values to zero:\n");
            Display(L);
            printf("\n");
            break;
        case 5:
            printf("Enter value x: ");
            scanf("%d", &x);
            L = Delete_occurences(L, x);
            printf("List after deleting repetitions:\n");
            Display(L);
            printf("\n");
            break;
        case 0: break;
        default: printf("Invalid option.\n");
            break;
        }
    }while (option != 0);
    return 0;
}
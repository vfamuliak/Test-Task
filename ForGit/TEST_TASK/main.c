#include<stdio.h>
#include<windows.h>
#include<stdlib.h>

#define MAX_LENGTH_MESS 25
#define MAX_LENGTH_LIST 5

typedef struct inform {
    int priority;
    char message[MAX_LENGTH_MESS];
} INFORM;

typedef struct list_elem {
    INFORM inf;
    struct list_elem *next, *prev;
} LIST_EL;

int input_data (INFORM *);
void InsertElem (INFORM);
void AddElem (LIST_EL *, LIST_EL *);
void DeleteLastElem ();
void PrintList ();

LIST_EL *list_begin, *list_end;  //вказівники на початок та кінець списку

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    puts("\t\tТестове завдання");
    INFORM input;
    while(input_data(&input)!=0)
        InsertElem(input);
    printf("\n\nДрук черги повідомлень:");
    PrintList();

    return 0;
}

int input_data (INFORM *data)
{
    static int num=0; //лічильник введених даних
    if(num>MAX_LENGTH_LIST) {
        printf("Новий елемент:\n\tВведіть пріоритет (кінець введення 0) - ");
        scanf("%d", &data->priority);
    }
    else {
        printf("%d елемент:\n\tВведіть пріоритет (кінець введення 0) - ", ++num);
        scanf("%d", &data->priority);
    }
    if(data->priority==0) {
        free(data);
        return 0;
    }
    if(num>MAX_LENGTH_LIST){
        printf("Досягнуто максимальної кількості записів.\nЗапис з найменшим пріоритетом буде видалено!!!\n");
        DeleteLastElem();
    }
    fflush(stdin);
    printf("\tВведіть повідомлення: ");
    gets(data->message);
    return data->priority;
}

void InsertElem (INFORM data)
{
    LIST_EL *new_el, *elem;
    new_el=(LIST_EL *)malloc(sizeof(LIST_EL));
    new_el->inf=data;

    if(list_begin==NULL) {
        new_el->next=new_el->prev=NULL;
        list_begin=list_end=new_el;
        return;
    }
    if(list_end->inf.priority < data.priority) {
        list_end->next=new_el;
        new_el->prev=list_end;
        new_el->next=NULL;
        list_end=new_el;
        return;
    }
    elem=list_begin;
    while(data.priority > elem->inf.priority && elem!=NULL)
        elem=elem->next;
    AddElem(new_el, elem); //new_el буде приєднано перед elem
}

void AddElem (LIST_EL *new_el, LIST_EL *old_el)
{
    if(old_el==list_begin) {
        list_begin->prev=new_el;
        new_el->next=list_begin;
        new_el->prev=NULL;
        list_begin=new_el;
        return;
    }
    if(old_el!=NULL) {
        new_el->next=old_el;
        new_el->prev=old_el->prev;
        old_el->prev->next=new_el;
        old_el->prev=new_el;
    }
    else {
            list_end->next=new_el;
            new_el->prev=list_end;
            new_el->next=NULL;
            list_end=new_el;
    }
}

void DeleteLastElem (void)
{
    LIST_EL *for_del=list_end;
    list_end=list_end->prev;
    list_end->next=NULL;
    free(for_del);
}

void PrintList (void)
{
    LIST_EL *el=list_begin;
    while(el!=NULL) {
        printf("\nПовідомлення: %-25s\n\tПріоритет - %d", el->inf.message, el->inf.priority);
        el=el->next;
    }
}

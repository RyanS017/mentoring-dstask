#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DESCRIPTION_SIZE 100

typedef struct Task {
    int id;
    char description[MAX_DESCRIPTION_SIZE];
    struct Task* prox;
} TASK;

TASK* queue = NULL;
TASK* list = NULL;
TASK* stack = NULL;
// CONSTRUCTOR
TASK* createTask(int id, char* description);
TASK* createTaskByScanf();

// LIST
void addToCompletedList(TASK* newTask);
TASK* removeFromCompletedListByItsId(int id);
void seeAllCompletedList();

// QUEUE
void putToPendingQueue(TASK* newTask);
TASK* getFromPendingQueue();
void seeAllPendingQueue();

// STACK
void pushToDraftStack(TASK* newTask);
TASK* popFromDraftStack();
void seeAllDraftStack();

// MENU
void displayMenu();

int main() {
    int choice;
    printf("################# TASK MANAGER SYSTEM #################");
    do {
        displayMenu();
        printf("Choose an option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                // CREATE A TASK, THEN ADD TO PENDING QUEUE
                TASK* newTask = createTaskByScanf();
                    putToPendingQueue(newTask);
                    break;


            case 2:
                // SEE ALL TASKS FROM PENDING QUEUE
                seeAllPendingQueue();
                break;

            case 3:
                // COMPLETE FIRST PENDING TASK
                TASK* firstTask = getFromPendingQueue();
                if(firstTask != NULL) {
                    addToCompletedList(firstTask);
                }
                break;

            case 4:
                // SEE ALL TASKS FROM COMPLETED LIST
                seeAllCompletedList();
                break;

            case 5:
                // SET COMPLETED TASK TO DRAFT
                int id;
                printf("Enter Task ID (number): ");
                scanf("%d", &id);

                TASK* task = removeFromCompletedListByItsId(id);
                if(task != NULL) {
                    pushToDraftStack(task);
                }
                break;

            case 6:
                // SEE ALL TASKS FROM DRAFT STACK
                seeAllDraftStack();
                break;

            case 7:
                // SET LAST DRAFT AS PENDING TASK
                TASK* lastTask = popFromDraftStack();
                if(lastTask != NULL) {
                    putToPendingQueue(lastTask);
                }
                break;

            case 0:
                printf("Exiting program\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 0);

    printf("################# SYSTEM SHUT DOWN #################");
}

// CONSTRUCTOR
TASK* createTask(int id, char* description) {
    TASK* newTask = (TASK*) malloc(sizeof(TASK));

    newTask->id = id;
    strcpy(newTask->description, description);
    newTask->prox = NULL;

    return newTask;
}

TASK* createTaskByScanf() {
    int id;
    char description[MAX_DESCRIPTION_SIZE];

    printf("Enter Task ID (number): ");
    scanf("%d", &id);

    getchar();
    printf("Enter Task Description (string): ");

    fgets(description, MAX_DESCRIPTION_SIZE, stdin);
    description[strcspn(description, "\n")] = '\0';

    return createTask(id, description);
}

// LIST
void addToCompletedList(TASK* newTask) {
    printf("\nAdding Task to Completed List\n");

        if(list == NULL){
            list = newTask;
            list->prox = NULL;
        }
        else{
            TASK* aux = list;
            while (aux->prox != NULL)
            {
                printf("%d\n", aux->id);
                aux = aux->prox;
            }
            aux->prox = newTask;
        }
    
}

TASK* removeFromCompletedListByItsId(int id) {
    printf("\nRemoving Task from Completed List\n");
    TASK* aux = list;
    TASK * aux2 = list;
    while(aux != NULL){
        if(aux->id == id)
        { 
            if(aux2 == aux && aux->prox == NULL) {
                list = NULL;
                return aux;
            }
            while(aux2->prox != aux && aux2 != aux){
                aux2 = aux2->prox;
            }
            if(aux->prox == NULL){
                aux2->prox = NULL;
                return aux;
                
            }
            if(list == aux){
                list = list->prox;
                aux->prox = NULL;
                return aux;
            }
            aux2->prox = aux2->prox->prox;    
            aux->prox = NULL;
            return aux;            
        }
        aux = aux->prox;
    }
    return NULL; // Return NULL if ID not exist
}

void seeAllCompletedList() {
    printf("\nPrinting All Completed List\n");

    TASK* aux = list;
    while (aux != NULL)
    {
        printf("\nId: %d\nDescription: %s", aux->id, aux->description);
        aux = aux->prox;
    }
    printf("\n");
}

// QUEUE
void putToPendingQueue(TASK* newTask) {
    printf("\nPutting Task to Pending Queue\n");
    
    if(queue == NULL){
        queue = newTask;
    }
    else{
        TASK* aux = queue;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = newTask;
        
    }
}

TASK* getFromPendingQueue() {
    printf("\nGetting Task from Pending Queue\n");
    if(queue == NULL){
        return  NULL;
    }
    TASK* aux = queue;
    TASK* aux2 = queue->prox;
    queue = aux2;
    aux->prox = NULL;
    return aux;
}

void seeAllPendingQueue() {
    printf("\nPrinting All Pending Queue\n");

    TASK* aux = queue;
    while (aux != NULL)
    {
        printf("\nId: %d\nDescription: %s", aux->id, aux->description);
        aux = aux->prox;
    }
    printf("\n");    
}

// STACK
void pushToDraftStack(TASK* newTask) {
    printf("\nPushing Task to Draft Stack\n");
    if(stack == NULL){
        stack = newTask;
        return;
    }
    TASK* aux = newTask;
    aux->prox = stack;
    stack = aux;
}

TASK* popFromDraftStack() {
    printf("\nPopping Task to Draft Stack\n");

    if(stack == NULL){
    return NULL; // Return NULL if Stack is empty
    }
    TASK* aux = stack;
    if(stack->prox != NULL){
        stack = stack->prox;
    }else{
        stack = NULL;
    }
    aux->prox = NULL;
    return aux;
}

void seeAllDraftStack() {
    printf("\nPrinting All Draft Stack\n");

    TASK* aux = stack;
    while (aux != NULL)
    {
        printf("\nId: %d\nDescription: %s", aux->id, aux->description);
        aux = aux->prox;
    }
    printf("\n"); 
}

// MENU
void displayMenu() {
    printf("\nMenu:\n");
    printf("1 - Create New Pending Task\n");
    printf("2 - See All Pending Tasks\n");
    printf("3 - Complete First Pending Task\n");
    printf("4 - See All Completed Tasks\n");
    printf("5 - Set Completed Task as Draft by its ID\n");
    printf("6 - See All Draft Tasks\n");
    printf("7 - Set Last Draft Task as Pending Task\n");
    printf("0 - Exit\n");
}

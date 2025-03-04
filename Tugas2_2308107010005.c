#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 100

int count = 0;

/* STACK ARRAY */
typedef struct {
    int items[MAX_SIZE];
    int top;
} stackArray;

/*Fungsi Untuk Membuat Stack Array Baru*/
void createEmptyStackArray(stackArray *s){
    s->top = -1;
}

//Cek apakah stack sudah penuh
int isArrayFull(stackArray *s){
    if(s->top == MAX_SIZE-1){
        return 1;
    }
    else {
        return 0;
    }
}

//Cek apakah stack masih kosong
int isArrayEmpty(stackArray *s){
    if(s->top == -1){
        return 1;
    }
    else {
        return 0;
    }
}

/*Fungsi push stack array*/
void pushArray(stackArray *s, char newItem){
    if(!isArrayFull(s)){
        s->top++;
        s->items[s->top] = newItem;
    }
}

/*Fungsi Pop Stack Array*/
char popArray(stackArray *s){
    if(!isArrayEmpty(s)){
        return s->items[s->top--];
    }
}

/*Fungsi Peek Stack Array*/
char peekArray(stackArray *s){
    if(!isArrayEmpty(s)){
        return s->items[s->top];
    }
    return '\0';
}

//POIN 1
bool isValidParentheses(char *expr){
    stackArray stack;
    createEmptyStackArray(&stack);

    for (int i = 0; expr[i] != '\0'; i++){
        char ch = expr[i];
        if(ch == '(' || ch == '{' || ch == '['){
            pushArray(&stack, ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']'){
            if(isArrayEmpty(&stack)) return false;
            char top = popArray(&stack);
            if((ch == ')' && top != '(') || (ch == '}' && top != '{') || (ch == '[' && top != ']')){
                return false;
            }
        }
    }
    return isArrayEmpty(&stack);
}

/*STACK LINKED LIST*/

typedef struct Node{
    char data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} stackList;

void createEmptyStackList(stackList *stack){
    stack->top = NULL;    
}

bool isListEmpty(stackList *stack){
    return stack->top == NULL;
}

void pushList(stackList *stack, char value){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

char popList(stackList *stack){
    if(isListEmpty(stack)) return '\0';
    Node *temp = stack->top;
    char value = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return value;
}

char peekList(stackList *stack){
    if (isListEmpty(stack)) return '\0';
    else{
        return stack->top->data;
    }
}

/*Poin 2*/
int priority(char ch){
    switch(ch){
        case '+': case '-' : return 1;
        case '*': case '/' : return 2;
        case '^' : return 3;
        default: return 0;
    }
}

void infixToPostfix(char infix[], char postfix[]){
    stackList stack;
    createEmptyStackList(&stack);
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++){
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[j++] = ch;
        }
        else if(ch == '('){
            pushList(&stack, ch);
        }
        else if(ch == ')'){
            while(!isListEmpty(&stack) && peekList(&stack) != '('){
                postfix[j++] = popList(&stack);
            }
            popList(&stack);
        }
        else {
            while(!isListEmpty(&stack) && priority(peekList(&stack)) >= priority(ch)){
                postfix[j++] = popList(&stack);
            }
            pushList(&stack, ch);
        }
    }

    while(!isListEmpty(&stack)){
        postfix[j++] = popList(&stack);
    }
    postfix[j] = '\0';
}

int evaluasiPostFix(char *postFix){
    stackList stack;
    createEmptyStackList(&stack);

    for (int i = 0; postFix[i] != '\0'; i++){
        char ch = postFix[i];

        if(isdigit(ch)){
            pushList(&stack, ch - '0');
        }
    }
}

int main(){
    char expression[MAX_SIZE];

    printf("Masukkan ekspresi tanda kurung: ");
    scanf("%s", expression);
    if(isValidParentheses(expression)){
        printf("Tanda Kurung Seimbang.\n");
    }
    else {
        printf("Tanda Kurung tidak seimbang.\n");
    }

    return 0;
}
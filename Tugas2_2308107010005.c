#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 100

int count = 0;

/* STACK ARRAY */
typedef struct {
    int items[MAX_SIZE];  // Array untuk menyimpan elemen
    int top; // menunjuk ke elemen paling atas
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
/*Validasi keseimbangna tanda kurung*/
bool isValidParentheses(char *expr){
    stackArray stack;
    createEmptyStackArray(&stack);

    for (int i = 0; expr[i] != '\0'; i++){
        char ch = expr[i];

        // Jika karakter adalah tanda buka kurung, push ke stack
        if(ch == '(' || ch == '{' || ch == '['){
            pushArray(&stack, ch);
        }

        //JIka karakter adalah tanda kurung, cek keseimbangan
        else if (ch == ')' || ch == '}' || ch == ']'){
            if(isArrayEmpty(&stack)) return false;
            char top = popArray(&stack);
            if  ((ch == ')' && top != '(') || 
                (ch == '}' && top != '{')  ||
                (ch == '[' && top != ']')) {
                return false;
            }
        }
    }
    return isArrayEmpty(&stack); // Harus kosong jika valid
}

/*STACK LINKED LIST*/

/*Struktur node untuk stack linked list*/
typedef struct Node{
    char data; // Data yang disimpan
    struct Node *next; // Pointer ke node berikutnya
} Node;

/*Struktur stack menggunakan linked list*/
typedef struct {
    Node *top; 
} stackList;

/*Inisialisasi Stack Linked List*/
void createEmptyStackList(stackList *stack){
    stack->top = NULL;    
}

/*Cek apakah Stack Linked List kosong*/
bool isListEmpty(stackList *stack){
    return stack->top == NULL;
}

/*Fungsi untuk menambahkan elemen ke stack Linked List*/
void pushList(stackList *stack, char value){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

/*Fungsi untuk menghapus elemen dari stack Linked List*/
char popList(stackList *stack){
    if(isListEmpty(stack)) return '\0';
    Node *temp = stack->top;
    char value = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return value;
}

/*Fungsi untuk memeriksa elemen teratas pada stack linked list*/
char peekList(stackList *stack){
    if (isListEmpty(stack)) return '\0';
    else{
        return stack->top->data;
    }
}

/*Poin 2*/
/*Menentukan prioritas operator*/
int priority(char operator){
    switch(operator){
        case '+': case '-' : return 1;
        case '*': case '/' : return 2;
        case '^' : return 3;
        default: return 0;
    }
}

/*Konversi ekspresi infix ke postfix*/
void infixToPostfix(char infix[], char postfix[]){
    stackList stack;
    createEmptyStackList(&stack);
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++){
        char ch =  infix[i];
        if (ch == ' ') continue;

        if (isdigit(ch)) {
            while (isdigit(infix[i])){
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        }
        else if(ch == '('){
            pushList(&stack, ch);
        }
        else if(ch == ')'){
            while(!isListEmpty(&stack) && peekList(&stack) != '('){
                postfix[j++] = popList(&stack);
                postfix[j++] = ' ';
            }
            popList(&stack);
        }
        else {
            while(!isListEmpty(&stack) && priority(peekList(&stack)) >= priority(ch)){
                postfix[j++] = popList(&stack);
                postfix[j++] = ' ';
            }
            pushList(&stack, ch);
        }
    }

    while(!isListEmpty(&stack)){
        postfix[j++] = popList(&stack);
        postfix[j++] = ' ';
    }
    postfix[j-1] = '\0';
}

/* Evaluasi PostFix */

int evaluasiPostFix(char postFix[]){
    stackArray stackArray;
    createEmptyStackArray(&stackArray);

    for (int i = 0; postFix[i] != '\0'; i++){
        if(postFix[i] == ' ') continue;

        if(isdigit(postFix[i])){
            int num = 0;
            while(isdigit(postFix[i])){
                num = num * 10 + (postFix[i++] - '0');
            }
            pushArray(&stackArray, num);
            i--;
        }
        else {
            int b = popArray(&stackArray);
            int a = popArray(&stackArray);

            switch (postFix[i]){
                case '+': pushArray(&stackArray, a + b); break;
                case '-': pushArray(&stackArray, a - b); break;
                case '*': pushArray(&stackArray, a * b); break;
                case '/': pushArray(&stackArray, a / b); break;
            }
        }
    }
    return popArray(&stackArray);
}

int main(){
    char expression[MAX_SIZE], postFix[MAX_SIZE], inFix[MAX_SIZE];

    printf("Masukkan ekspresi tanda kurung: ");
    scanf("%s", expression);
    if(isValidParentheses(expression)){
        printf("Tanda Kurung Seimbang.\n");
    }
    else {
        printf("Tanda Kurung tidak seimbang.\n");
    }

    printf("Masukkan ekspresi aritmatika infix: ");
    scanf("%s", inFix);
    infixToPostfix(inFix, postFix);
    printf("Postfix: %s\n", postFix);

    printf("Hasil evaluasi postfix: %d\n", evaluasiPostFix(postFix));   

    return 0;
}
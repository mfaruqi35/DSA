#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define ALPHABET_SIZE 26

// Struktur Node untuk Linked List
typedef struct Node {
    char word[MAX_WORD_LENGTH];
    struct Node *next;
} Node;

// Array berisi pointer ke linked list
Node *wordLists[ALPHABET_SIZE] = {NULL};

// Fungsi untuk membuat node baru
Node* createNode(char *word) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newNode->word, word);
    newNode->next = NULL;
    return newNode;
}

// Fungsi untuk menambahkan kata ke linked list
void insertWord(char *word) {
    if (!word || word[0] == '\0') return;
    int index = tolower(word[0]) - 'a';
    if (index < 0 || index >= ALPHABET_SIZE) return;
    
    Node *newNode = createNode(word);
    newNode->next = wordLists[index];
    wordLists[index] = newNode;
}

// Fungsi untuk menampilkan kata berdasarkan huruf pertama
void displayWords(char letter) {
    int index = tolower(letter) - 'a';
    if (index < 0 || index >= ALPHABET_SIZE) {
        printf("Huruf tidak valid!\n");
        return;
    }
    
    Node *current = wordLists[index];
    if (!current) {
        printf("Kata dengan huruf awal %c tidak ditemukan.\n", letter);
        return;
    }
    
    printf("Kata-kata dengan huruf awal %c:\n", letter);
    int count = 0;
    while (current && count < 25) {
        printf("%s\n", current->word);
        current = current->next;
        count++;
    }
}

// Fungsi untuk menghapus kata dari linked list
void deleteWord(char *word) {
    int index = tolower(word[0]) - 'a';
    if (index < 0 || index >= ALPHABET_SIZE) return;
    
    Node *current = wordLists[index], *prev = NULL;
    while (current) {
        if (strcmp(current->word, word) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                wordLists[index] = current->next;
            }
            free(current);
            printf("Kata '%s' berhasil dihapus.\n", word);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Kata '%s' tidak ditemukan.\n", word);
}

// Fungsi untuk membaca file dan mengisi struktur data
void readFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Gagal membuka file!\n");
        return;
    }
    
    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) == 1) {
        insertWord(word);
    }
    
    fclose(file);
    printf("Pembacaan isi file selesai.\n");
}

// Fungsi untuk membebaskan seluruh memori
void freeMemory() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        Node *current = wordLists[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
        wordLists[i] = NULL;
    }
}

int main() {
    char filename[] = "dbterms.txt";
    readFile(filename);
    
    int choice;
    char input[MAX_WORD_LENGTH];
    do {
        printf("\nMenu Pilihan:\n");
        printf("1) Menampilkan kata-kata sesuai huruf pertama yang ditentukan\n");
        printf("2) Menghapus kata tertentu dalam linked list\n");
        printf("3) Selesai\n");
        printf("Pilihan anda: ");
        scanf(" %d", &choice);
        
        switch (choice) {
            case 1:
                printf("Huruf: ");
                scanf(" %s", input);
                displayWords(input[0]);
                break;
            case 2:
                printf("Kata yang ingin dihapus: ");
                scanf(" %s", input);
                deleteWord(input);
                break;
            case 3:
                freeMemory();
                printf("Program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (choice != 3);
    
    return 0;
}

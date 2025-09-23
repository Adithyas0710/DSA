#include <stdio.h>
#include <stdlib.h>


typedef struct Block {
    int start_address;
    int size;
    struct Block* next;
    struct Block* prev;
} Block;

Block* head = NULL;


Block* create_block(int start, int size) {
    Block* new_block = (Block*)malloc(sizeof(Block));
    new_block->start_address = start;
    new_block->size = size;
    new_block->next = NULL;
    new_block->prev = NULL;
    return new_block;
}


void add_block(int start, int size) {
    Block* new_block = create_block(start, size);

    if (head == NULL) {
        head = new_block;
        return;
    }

    Block* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new_block;
    new_block->prev = temp;
}


void display_free_blocks() {
    printf("Free Memory Blocks:\n");
    Block* temp = head;
    while (temp != NULL) {
        printf("Start: %d  Size: %d\n", temp->start_address, temp->size);
        temp = temp->next;
    }
    printf("\n");
}


void first_fit_allocate(int request_size) {
    Block* temp = head;

    while (temp != NULL) {
        if (temp->size >= request_size) {
            printf("Memory allocated at: %d\n", temp->start_address);

            if (temp->size == request_size) {
                
                if (temp->prev == NULL) {
                    
                    head = temp->next;
                    if (head != NULL) head->prev = NULL;
                } else if (temp->next != NULL) {
                    
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                } else {
                    
                    temp->prev->next = NULL;
                }
                free(temp);
            } else {
                
                temp->start_address += request_size;
                temp->size -= request_size;
            }
            return;
        }
        temp = temp->next;
    }

    printf("Allocation failed: No sufficient memory block available\n");
}

int main() {
    int n, start, size;

    printf("Enter number of free memory blocks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter start address for block %d: ", i + 1);
        scanf("%d", &start);

        printf("Enter size for block %d: ", i + 1);
        scanf("%d", &size);

        add_block(start, size);
    }

    display_free_blocks();

    int request_size;
    char choice = 'y';

    while (choice == 'y' || choice == 'Y') {
        printf("Enter process size to allocate: ");
        scanf("%d", &request_size);

        first_fit_allocate(request_size);
        display_free_blocks();

        printf("Do you want to allocate another process? (y/n): ");
        scanf(" %c", &choice);  
    }

    return 0;
}


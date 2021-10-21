#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

long init_buffer_421(void);
long insert_buffer_421(int);
long print_buffer_421(void);
long delete_buffer_421(void);

// Global Variable
static ring_buffer_421_t *buffer = NULL;

long init_buffer_421() {

    // If the buffer is empty, initialize it
    if (buffer == NULL) {
    
        buffer = (ring_buffer_421_t*)malloc(sizeof(ring_buffer_421_t));

        // malloc failed, returning NULL; thus do not continue
        if (buffer == NULL) {
            return -1;
        }
        
        buffer->length = 0;
        
        buffer->write = (node_421_t*)malloc(sizeof(node_421_t));
        
        // malloc failed, returning NULL; thus do not continue
        if (buffer->write == NULL) {
            return -1;
        }
        
        buffer->write->data = 0;
        
        
        // This is supposed to switch bufferWrite to bufferRead and
        // have bufferRead point to itself...not sure if it works completely
        buffer->read = buffer->write;    
        buffer->read->next = buffer->read;
        
        for (int i = 0; i < 19; i++) {
            buffer->write = (node_421_t*)malloc(sizeof(node_421_t));
            
            // malloc failed, returning NULL; thus do not continue
            if (buffer->write == NULL) {
                return -1;
            }

            buffer->write->data = 0;
            buffer->write->next = buffer->read->next;
            
            buffer->read->next = buffer->write;
            buffer->read = buffer->write; 
            
        }
        
        buffer->write = buffer->read;
    
        return 0;
    }
    
    // Else, the buffer wasn't initialized,
    // so we don't initialize it and we return -1;
    // Fail for any other reason? What kind of reason?
    return -1;
}




long insert_buffer_421(int i) {
    
    if (buffer != NULL) {
        if (buffer->length < 20) {
            
            buffer->write->data = i;
            buffer->write = buffer->write->next;
            
            buffer->length += 1;
        } else {

            // Buffer is already full with 20 nodes, so
            // we don't add the integer and we return -1
            printf("\nBuffer is already at max capacity");
            return -1;
        }
        
        return 0;
    }

    // Else, the buffer wasn't initialized,
    // so we don't add the integer and we return -1    
    return -1;
    
}

// Change the formatting?
long print_buffer_421() {
    
    if (buffer != NULL) {
        
        printf("Number of elements in buffer: %d\n", buffer->length);
        
        // Should I use the read pointer from buffer solely for iterating?
        node_421_t *temp = buffer->read;
        //printf("\n");        
        for (int i = 0; i < buffer->length; i++) {
            
            printf("Node %d: ", i+1);
            printf("%d\n", temp->data);
            
            temp = temp->next;
        }
        // Everything worked properly, so return 0
        return 0;
    }
    
    // Else, the buffer wasn't initialized,
    // so we don't print and return -1.
    return -1;
}



long delete_buffer_421() {        
        
    if (buffer != NULL) {    

        for (int i = 0; i < 20; i++) {
            node_421_t *temp = buffer->read->next;
            buffer->read->next = buffer->read->next->next;
        
            free(temp);
            temp = NULL;
        }
    
        free(buffer);
        buffer = NULL;
        
        return 0;
    }

    // Else, the buffer wasn't initialized,
    // so we don't delete and return -1.
    return -1;
}

// Delete this for kernel code
int main() {

    //Testing

    int buff_func_before_initialized = print_buffer_421();
    printf("Trying to print before initialized (expected output = -1): %d\n", 
        buff_func_before_initialized);
    
    buff_func_before_initialized = insert_buffer_421(5);
    printf("Trying to insert before initialized (expected output = -1): %d\n", 
        buff_func_before_initialized); 
    
    buff_func_before_initialized = delete_buffer_421();
    printf("Trying to delete before initialized (expected output = -1): %d\n", 
        buff_func_before_initialized);



    int doubleInitialization = init_buffer_421();    
    printf("\nInitializing buffer first time (expected output = 0): %d\n", 
        doubleInitialization);   
    
    doubleInitialization = init_buffer_421();    
    printf("Initializing buffer second time (expected output = -1): %d\n", 
        doubleInitialization);
    
    printf("\nAttempting to insert 22 elements; expect 2 max capactiy error messages:");
    for (int i = 0; i < 20; i++) {
        insert_buffer_421(i+1);
    }
    
    insert_buffer_421(21);
    insert_buffer_421(-1);
    
    printf("\n");
    print_buffer_421();
        
    
    int bufferDoubleDelete = delete_buffer_421();
    printf("\nDeleteing buffer first time (expected output = 0): %d\n", 
        bufferDoubleDelete);
    
    bufferDoubleDelete = delete_buffer_421();
    printf("Deleteing buffer second time (expected output = -1): %d\n", 
        bufferDoubleDelete);
}

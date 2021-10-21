#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

long init_buffer_421(void);
long insert_buffer_421(int);
long print_buffer_421(void);
long delete_buffer_421(void);


static ring_buffer_421_t *buffer = NULL;

long init_buffer_421() {

    // If the buffer is empty, initialize it
    if (buffer == NULL) {
    
        buffer = (ring_buffer_421_t*)malloc(sizeof(ring_buffer_421_t));
        buffer->length = 0;
        
        buffer->write = (node_421_t*)malloc(sizeof(node_421_t));
        buffer->write->data = 0;
        
        
        // This is supposed to switch bufferWrite to bufferRead and
        // have bufferRead point to itself...not sure if it works completely
        buffer->read = buffer->write;    
        buffer->read->next = buffer->read;
        
        for (int i = 0; i < 19; i++) {
            buffer->write = (node_421_t*)malloc(sizeof(node_421_t));

            buffer->write->data = 0;
            buffer->write->next = buffer->read->next;
            
            buffer->read->next = buffer->write;
            buffer->read = buffer->write; 
            
        }
        
        int bufferLength = buffer->length;
        printf("\nLength of buffer: %d\n", bufferLength);
        
        int nodeData = buffer->read->data;
        printf("Data of read node: %d\n\n", nodeData);
        
        buffer->write = buffer->read;
    
        return 0;
    }
    
    
    return -1;

/*
	node_421_t  *readHead = (node_421_t*)malloc(sizeof(node_421_t));
    node_421_t  *writeHead = (node_421_t*)malloc(sizeof(node_421_t));

	readHead->data = 0;
	readHead->next = NULL;

	// Creates the first node in the ring buffer
	// For loop below creates 19 more nodes for a total of 20 nodes
	writeHead->data = 0;
	writeHead->next = NULL;


	node_421_t *curr = writeHead;

	for (int i = 0; i < 19; i++) {
		node_421_t *temp = (node_421_t*)malloc(sizeof(node_421_t));
		temp->data = 0;
		temp->next = NULL;

		curr->next = temp;
		curr = curr->next;

		if (i == 18) {
			curr->next = writeHead;
		}
	}


	buffer = (ring_buffer_421_t*)malloc(sizeof(ring_buffer_421_t));
	buffer->length = 20;
	buffer->read = readHead;
	buffer->write = writeHead;

	//--------------------------------------------------------------------------------------------
	// This part (and below) needs to go in delete_buffer
	node_421_t *currentDelete = writeHead;

	for (int i = 0; i < 20; i++) {
		node_421_t *temp = currentDelete->next;

		free(currentDelete);
		currentDelete = NULL;
		currentDelete = temp;
	}

	free(readHead);		// This will go in delete_buffer
	free(buffer);
	//free(writeHead);	// At the beginning, I thought I needed this, but I'm pretty sure my for-loop deletes all of the nodes in writeHead
*/
}




long insert_buffer_421(int i) {
    
    if (buffer != NULL) {
        if (buffer->length < 20) {
            
            buffer->write->data = i;
            buffer->write = buffer->write->next;
            
            buffer->length += 1;
        } else {
            
            printf("\nBuffer is already at max capacity\n");
            return -1;
        }
        
        return 0;
    }
    
    return -1;
    
}


long print_buffer_421() {
    
    if (buffer != NULL) {
        
        printf("\nRelative to read node position in linked list:\n");
        
        // Should I use the read pointer from buffer solely for iterating?
        node_421_t *temp = buffer->read;
        //printf("\n");        
        for (int i = 0; i < buffer->length; i++) {
            
            printf("Node %d: ", i+1);
            printf("%d\n", temp->data);
            
            temp = temp->next;
        }
        
        return 0;
    }
    
    return -1;
}



long delete_buffer_421() {        
        
        if (buffer != NULL) {    

            for (int i = 0; i < 20; i++) {
                node_421_t *temp = buffer->read->next;
                buffer->read->next = buffer->read->next->next;
            
                free(temp);
            }
        
            free(buffer);
            
            return 0;
        }

        
        return -1;
}

int main() {

    printf("BEFORE BUFFER CREATED\n");
	if (init_buffer_421() == 0) {
	    printf("BUFFER SUCCESSFULLY CREATED; returning 0");	
	    
	    insert_buffer_421(1);
	    insert_buffer_421(2);
	    insert_buffer_421(3);
	    insert_buffer_421(4);
	    insert_buffer_421(5);
	    insert_buffer_421(6);
	    insert_buffer_421(7);
	    insert_buffer_421(8);
  	    /*insert_buffer_421(8);
  	    insert_buffer_421(8);
  	    insert_buffer_421(8);
  	    insert_buffer_421(8);
  	    insert_buffer_421(8);
  	    insert_buffer_421(8);
  	    insert_buffer_421(8);
  	    insert_buffer_421(8);
  	    insert_buffer_421(8);
  	    insert_buffer_421(8);
  	    insert_buffer_421(8);
  	    insert_buffer_421(8);*/
	    
	    print_buffer_421();
	    
	    delete_buffer_421();
        printf("FREED BUFFER MEMORY\n");
	}


}

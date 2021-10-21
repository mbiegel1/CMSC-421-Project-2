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
        
        buffer->write = (node_421_t*)malloc(sizeof(node_421_t));
        buffer->write->data = 0;
        
        // This is supposed to switch bufferWrite to bufferRead and
        // have bufferRead point to itself...not sure if it works completely
        buffer->read = buffer->write;    
        buffer->read->next = buffer->read;
            
        buffer->length += 1;
        
        for (int i = 0; i < 19; i++) {
            buffer->write = (node_421_t*)malloc(sizeof(node_421_t));

            buffer->write->data = 0;
            buffer->write->next = buffer->read->next;
            
            buffer->read->next = buffer->write;
            buffer->read = buffer->write; 
            
            buffer->length += 1;   
        }
        
        // Can't print buffer using printf?????
        int bufferLength = buffer->length;
        //printf("Length of buffer: %d\n", bufferLength);
        
        int nodeData = buffer->read->data;
        printf("Data of read node: %d\n", nodeData);
        
    
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
}


long print_buffer_421() {
}



long delete_buffer_421() {        
        
        if (buffer != NULL) {    
            // Testing memory deletion
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
	init_buffer_421();
	printf("AFTER BUFFER CREATED\n");
	delete_buffer_421();
    printf("FREED BUFFER MEMORY\n");

}

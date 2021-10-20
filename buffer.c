#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

long init_buffer_421(void);
long insert_buffer_421(int);
long print_buffer_421(void);
long delete_buffer_421(void);



long init_buffer_421() {

	struct node_421  *readHead = (struct node_421*)malloc(sizeof(struct node_421));
        struct node_421  *writeHead = (struct node_421*)malloc(sizeof(struct node_421));

	readHead->data = 0;
	readHead->next = NULL;

	// Creates the first node in the ring buffer
	// For loop below creates 19 more nodes for a total of 20 nodes
	writeHead->data = 0;
	writeHead->next = NULL;

	
	struct node_421 *curr = writeHead;

	for (int i = 0; i < 19; i++) {
		struct node_421 *temp = (struct node_421*)malloc(sizeof(struct node_421));
		temp->data = 0;
		temp->next = NULL;

		curr->next = temp;
		curr = curr->next;
		
		printf("Time\n");
	}

	struct ring_buffer_421 buffer = {.length = 20, .read = readHead, .write = writeHead};


	struct node_421 *currentDelete = writeHead;

	for (int i = 0; i < 20; i++) {
		struct node_421 *temp = currentDelete->next;
		
		free(currentDelete);
		currentDelete = NULL;
		currentDelete = temp;
	}

	free(readHead);		// This will go in delete_buffer
	//free(writeHead);	// This will go in delete_buffer
}


int main() {

        printf("BEFORE BUFFER CREATED\n");
	init_buffer_421();
	printf("AFTER BUFFER CREATED\n");

}

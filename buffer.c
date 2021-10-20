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

	writeHead->data = 0;
	writeHead->next = NULL;

	struct ring_buffer_421 buffer = {.length = 20, .read = readHead, .write = NULL};

	free(readHead);
	free(writeHead);
}


int main() {

        printf("BEFORE BUFFER CREATED\n");
	init_buffer_421();
	printf("AFTER BUFFER CREATED\n");

}
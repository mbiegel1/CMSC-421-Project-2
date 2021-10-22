#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include "buffer.h"


// Global Variable
static ring_buffer_421_t *buffer = NULL;

SYSCALL_DEFINE0(init_buffer_421) {
    // Had to put this at the top because of warning from C90
    int i;
    
    // If the buffer is empty, initialize it
    if (buffer == NULL) {
    
        buffer = (ring_buffer_421_t*)kmalloc(sizeof(ring_buffer_421_t), 
            GFP_KERNEL);

        // malloc failed, returning NULL; thus do not continue
        if (buffer == NULL) {
            return -1;
        }
        
        buffer->length = 0;
        
        buffer->write = (node_421_t*)kmalloc(sizeof(node_421_t), GFP_KERNEL);
        
        // malloc failed, returning NULL; thus do not continue
        if (buffer->write == NULL) {
            return -1;
        }
        
        buffer->write->data = 0;
        
        
        // This is supposed to switch bufferWrite to bufferRead and
        // have bufferRead point to itself...not sure if it works completely
        buffer->read = buffer->write;    
        buffer->read->next = buffer->read;
        
        for (i = 0; i < 19; i++) {
            buffer->write = (node_421_t*)kmalloc(sizeof(node_421_t), 
                GFP_KERNEL);
            
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



SYSCALL_DEFINE1(insert_buffer_421, int, i) {    

    if (buffer != NULL) {
        if (buffer->length < 20) {
            
            buffer->write->data = i;
            buffer->write = buffer->write->next;
            
            buffer->length += 1;
        } else {

            // Buffer is already full with 20 nodes, so
            // we don't add the integer and we return -1
            printk("\nBuffer is already at max capacity");
            return -1;
        }
        
        return 0;
    }

    // Else, the buffer wasn't initialized,
    // so we don't add the integer and we return -1    
    return -1;
    
}


SYSCALL_DEFINE0(print_buffer_421) {
    // Had to put these at the top because of warning from C90
    int i;
    node_421_t *temp = buffer->read;    
    
    if (buffer != NULL) {
        
        printk("Number of elements in buffer: %d\n", buffer->length);
              
        for (i = 0; i < buffer->length; i++) {
            
            printk("Node %d: ", i+1);
            printk("%d\n", temp->data);
            
            temp = temp->next;
        }
        // Everything worked properly, so return 0
        return 0;
    }
    
    // Else, the buffer wasn't initialized,
    // so we don't print and return -1.
    return -1;
}


     
SYSCALL_DEFINE0(delete_buffer_421) {
    // Had to put these at the top because of warning from C90
    int i;
    
    if (buffer != NULL) {    
        
        for (i = 0; i < 20; i++) {
            node_421_t *temp = buffer->read->next;
            buffer->read->next = buffer->read->next->next;
        
            kfree(temp);
            temp = NULL;
        }
    
        kfree(buffer);
        buffer = NULL;
        
        return 0;
    }

    // Else, the buffer wasn't initialized,
    // so we don't delete and return -1.
    return -1;
}

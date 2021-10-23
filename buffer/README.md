### Class:   CMSC 421
### Project: 2
### File:    README.MD
### Author:  Mark Biegel
### Date:    10/29/21
### E-mail:  mbiegel1@umbc.edu


# Description:
  This project interacts with the kerenl by implementing a ciruclar buffer that 
  will be filled with integers and allows the buffer to be printed to the kernel
  log. Once completed, the buffer will be deleted so there are no memory leaks
  
# Project Files:
    `buffer.c` - The main file that contains the circular buffer
    `buffer.h` - Header file for `buffer.c`
    `test.c` - File that contains test functionality for the circular buffer
    `Makefile` - File to compile and run `buffer.c` in the kernel
    `README.md` - File describing Project 2 as well as my approach to it
  
# Thought Process:

    ###Process for Approaching Each System Call:
        1) `long init_buffer_421(void)
        I knew that a link list was required, and I knew how to implement a 
        linked list; however, I was unsure why there were 2 nodes `read` and 
        `write` for the ciruclar buffer. After talking with some peers, I 
        realized that maybe it will be used in the next project since that will
        encompass read/write capabilities of threads. So after figuring out a 
        way to use read/write nodes in the linked list, I made sure that all 
        space was allocated with kmalloc() properly and ensured that if it was 
        NOT successful (even if kmalloc() fails or the buffer is already 
        initialized), then it would return -1 or else 0.
        
        2) `long insert_buffer_421(int i)`
        I knew that for my implementation, the write node would be the one to 
        keep track of the next available node, so wherever it was located, I 
        would update the passed-in integer and increment the buffer length. It 
        will fail and return -1 if the buffer is already full by displaying an 
        error message and won't add the next integer or else 0.
        
        3) `long print_buffer_421(void)`
        I used a for-loop to print each element in the buffer starting at the 
        read node and printing from there. It prints each node's data on a new 
        line.
        
        4) `long delete_buffer_421(void)`
        I used a for-loop and a temp node variable to access each node in the 
        ciruclar buffer to free it and set it to NULL. Then once all the nodes 
        were free, I freed the buffer and set it to NULL as well. I returned 0 
        if everything went smoothly; else I returned -1 if the buffer was 
        already NULL.
    
    ###Process for Adding the Methods as System Calls:
        For this part, I started out in user space, so the first step to swtich 
        to kernel space was to change all of the `malloc()` to `kmalloc()`, 
        `free()` to `kfree()`, and `printf()` to `printk()`. `kmalloc()` takes 
        in 2 parameters unlike `malloc()` one parameter, so I used the first 
        parameter from `malloc()` in `kmalloc()` and the second parameter is 
        `GFP_KERNEL`. Then, I followed the directions from Part 4 to add the 
        functions add system calls to the kernel, and after playing around with 
        it, I was able to get the kernel to compile and install. Finally, I made
        a `test_c` folder which includes a `test.c` file that tests the buffer's
        capabilities in kernel code. After some quick tests, it seems that the 
        kernel code works well.




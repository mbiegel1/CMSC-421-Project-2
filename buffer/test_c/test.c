#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#define __NR_init_buffer_421 442
#define __NR_insert_buffer_421 443
#define __NR_print_buffer_421 444
#define __NR_delete_buffer_421 445

long init_buffer_syscall(void) {
    return syscall(__NR_init_buffer_421);
}

long insert_buffer_syscall(int i) {
    return syscall(__NR_insert_buffer_421, i);
}

long print_buffer_syscall(void) {
    return syscall(__NR_print_buffer_421);
}

long delete_buffer_syscall(void) {
    return syscall(__NR_delete_buffer_421);
}




int main(int argc, char *argv[]) {
    long init;
    long insert;
    long print;
    long delete;
    
    init = init_buffer_syscall();
    
    for (int i = 0; i < 20; i++) {
        insert = insert_buffer_syscall(i);
    }
    
    // Uncomment to cause insert to throw an error
    //insert = insert_buffer_syscall(-1);
    print = print_buffer_syscall();
    delete = delete_buffer_syscall();
    
    printf("\ninit number: %d", init);
    printf("\ninsert number: %d", insert);
    printf("\nprint number: %d", print);
    printf("\ndelete number: %d\n", delete);
    
    if(init < 0) {
        perror("init syscall failed");
    } else if (delete < 0) {
        perror("delete syscall failed");
    } else if (insert < 0) {
        perror("insert syscall failed");
    } else if (print < 0) {
        perror("print syscall failed");
    } else {
        printf("All syscalls ran successfully, check dmesg output\n");
    }
    
    
    return 0;
}


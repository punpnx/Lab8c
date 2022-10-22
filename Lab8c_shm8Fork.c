#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
int main() {
    int *count;

    int shmid;
    /* Q5.1 a or b? write the whole statement */
    /*a shmid = shmget(key,sizeof(int),0666|IPC_CREAT); */
    /*b*/shmid = shmget(IPC_PRIVATE,sizeof(int),0666|IPC_CREAT);
    
    // shmat to attach to shared memory
    count = /* Q5.2 */ shmat(shmid, NULL, 0);
    
    count[0] = 5;

    pid_t pid;
    if ((pid = fork()) == 0) { //child
        int temp = count[0]; sleep(1); temp = temp - 1;
        count[0] = temp; /* Q5.3 */
        printf("child decrements value at %p\n", &count);
        exit(0);
    }
    //wait(NULL);
    int temp = count[0]; sleep(1); temp = temp + 1;
    count[0] = temp;
    printf("parent increments value at %p\n",&count);
    sleep(1);
    printf("final answer is %d\n",count[0]);
    
    //detach from shared memory
    shmdt(count);
    // destroy the shared memory
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
} //main

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
    while (true)
    int i;
    void *shared_memory;
    char* temp;
    int shmid;
    shmid = shmget((key_t)2345, 1024, 0666);
    shared_memory = shmat(shmid, NULL, 0); // process attached to shared memory segment
    {
        if ((char *)shared_memory != temp)
        {
            printf("Key of shared memory is %d\n", shmid);
            printf("Process attached at %p\n", shared_memory);
            printf("Data read from shared memory is : %s\n", (char *)shared_memory);
            temp = (char *)shared_memory;
        }
    }

}
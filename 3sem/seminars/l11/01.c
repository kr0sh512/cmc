#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
    key_t key = ftok("/dev/null", 0);

    int semid = semget(key, 2, 0666 | IPC_CREAT);
    int shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT);

    int *shm = shmat(shmid, NULL, 0);
    semctl(semid, 0, SETVAL, 1);
    semctl(semid, 1, SETVAL, 1);

    pid_t pid = fork();
    if (!pid) {
        for (;;) {
            semop(semid, &(struct sembuf){.sem_num = 0, .sem_op = -1}, 1);
            semop(semid, &(struct sembuf){.sem_num = 1, .sem_op = -1}, 1);

            int r = scanf("%d", shm);
            if (r == -1) {
                break;
            }
            semop(semid, &(struct sembuf){.sem_num = 0, .sem_op = 1}, 1);
        }
        semctl(semid, 2, IPC_RMID, NULL);
        exit(0);
    } else if (pid == -1) {
        exit(1);
    }

    pid = fork();
    if (!pid) {
        for (;;) {
            if (semop(semid, &(struct sembuf){.sem_num = 0, .sem_op = -1}, 1) == -1) {
                break;
            }

            printf("$ %d\n", *shm);
            if (semop(semid, &(struct sembuf){.sem_num = 0, .sem_op = 1}, 1) == -1) {
                break;
            }
            if (semop(semid, &(struct sembuf){.sem_num = 1, .sem_op = 1}, 1) == -1) {
                break;
            }
        }
        exit(0);
    } else if (pid == -1) {
        exit(1);
    }

    while (wait(NULL) != -1)
        ;

    return 0;
}

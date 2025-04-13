#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>

struct record
{
    double dbl, int num,
}

int
main(int argc, char **argv)
{
    int shm_key = shmget(IPC_PRIVATE, sizeof(record), IPC_CREAT | 0666);
    int sem_key = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);

    record *mem = shmat(shm_key, NULL, 0);

    for (int i = 1; i < argc; ++i) {
        int fd = open(argv[i], O_RDONLY);
        double sum = 0;
        int num = 0;
        double tmp;

                while (read(fd, &tmp, sizeof(tmp)) {
            num++;
            sum += tmp;
		}
		semop(sem_key, &(struct sembuf){.sem_num = 0, .sem_op = -2}, 1);
		*mem = (struct record){.dbl = sum, .num = num};
		semop(sem_key, &(struct sembuf){.sem_num = 0, .sem_op = -1}, 1);
    }

    while (wait(NULL) != -1) {
    }

    return 0;
}

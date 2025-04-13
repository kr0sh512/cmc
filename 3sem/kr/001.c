#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/file.h>

int main(int argc, char** argv){

    int id_of_shm = shmget(argv[1], sizeof(double) * 2, IPC_CREAT | 0666);
    float* start_of_shm = shmat(id_of_shm, NULL, 0);

    int sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    semctl(sem_id, 0, SETVAL, 1);

    struct sembuf p = {0, -1, 0}, v = {0,1,0};
    

    for(int i = 2; i < argc; i++){
        pid_t pid = fork();
        
        if (pid == 0) {
            FILE* in_file = fopen(argv[i], "r");
            float sum = 0, n = 0;
            float buf;
            while(fscanf(in_file, "%f", &buf) != EOF){
                sum += buf;
                n++;
            }

            semop(sem_id, &p, 1);
            start_of_shm[1] += sum;
            start_of_shm[0] += n;
            semop(sem_id, &v, 1);

            fclose(in_file);
            
            return 0;
        }

    }

    
    while (wait(NULL) != -1 ){
    }
    printf("%f\n", start_of_shm[1] / start_of_shm[0]);
    
    semctl(sem_id, 0, IPC_RMID);
    shmctl(id_of_shm, IPC_RMID, NULL);
    

    return 0;
}

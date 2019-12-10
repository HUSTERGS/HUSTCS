#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

int semid;

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO */
};

void P(int semid, int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = SEM_UNDO;
    semop(semid, &sem, 1);
    return ;
}

void V(int semid, int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = SEM_UNDO;
    semop(semid, &sem, 1);
    return ;
}


int main(void) {
    // int semid;
    struct sembuf sembuf;
    int share_id;
    share_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    
    if ((semid = semget(IPC_PRIVATE, 0, 0)) == -1) {
        // 如果信号灯集不存在的话，就创建两个信号灯
        if ((semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666)) != -1) {
            // 如果创建成功
            union semun arg0;
            union semun arg1;
            arg0.val = 0;
            arg1.val = 1;
            // 设置信号灯的量分别为0,1
            if (semctl(semid, 1, SETVAL, arg1) == -1 || semctl(semid, 0, SETVAL, arg0) == -1) {
               perror("IPC error 1: semctl");
               exit(1); 
            }

            int p1 = fork();
            if (p1 == 0) {
                // 在子进程1
                for (int i = 1; i <= 100; i++) {
                    P(semid, 0);
                    printf("%d th Calculation: %d\n", i, *(int *)shmat(share_id, NULL, SHM_RDONLY));
                    V(semid, 1);
                }
            } else {
                int p2 = fork();
                if (p2 == 0) {
                    // 第二个子进程
                    for (int i = 1; i <= 100; i++) {
                        P(semid, 1);
                        int * temp = (int *)shmat(share_id, NULL, SHM_W);
                        *temp += i;
                        // sleep(1);
                        V(semid, 0);
                    }
                } else {
                    waitpid(p1, NULL, 0);
                    waitpid(p2, NULL, 0);
                    // 销毁信号灯
                    if (semctl(semid, 0, IPC_RMID) == -1) {
                        perror("Destroy Semaphore Failed!\n");
                    }
                }
            }
        } else {
            perror("IPC error 2: semget");
            exit(1);
        }
    } else {
        perror("Semaphore is allready created!");
        exit(1);
    }
    return 0;
}

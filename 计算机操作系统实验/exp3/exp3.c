#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <stdbool.h>
#define BUFFSIZE 10


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
// 

int main(void) {
    // 信号灯集
    int semid;
    // 创建共享分区，大小为buff
    int share_buffer = shmget(IPC_PRIVATE, sizeof(unsigned char) * BUFFSIZE, IPC_CREAT | 0666);
    // 两个Index, in_index和out_index
    int finish_flag = shmget(IPC_PRIVATE, sizeof(bool), IPC_CREAT | 0666);
    int in_index_id = shmget(IPC_PRIVATE, sizeof(long long), IPC_CREAT | 0666);
    *(int *)shmat(in_index_id, NULL, SHM_R) = 0;
    // 先暂时这么写
    const char * source = "input.txt";
    const char * target = "output.txt";
    // const char * source = "exp3.pdf";
    // const char * target = "test.pdf";
    // const char * source = "source.png";
    // const char * target = "output.png";
    // 测试文件是否可以正常访问
    FILE * source_file = fopen(source, "r");
    if (source_file == NULL) {
        printf("源文件不存在\n");
        exit(EXIT_FAILURE);
    }

    FILE * target_file = fopen(target, "w");
    if (target_file == NULL) {
        printf("目标文件打开失败\n");
        exit(EXIT_FAILURE);
    }
    fclose(source_file);
    fclose(target_file);

    if ((semid = semget(IPC_PRIVATE, 0, 0) == -1)) {
        // 如果信号灯集不存在的话，就创建三个信号灯,第三个信号灯用于判断是否完成
        if ((semid = semget(IPC_PRIVATE, 3, IPC_CREAT | 0666)) != -1) {
            // 如果创建成功
            union semun w_arg; // 用于写进程的参数
            union semun r_arg; // 用于读进程的参数
            union semun lock;
            w_arg.val = BUFFSIZE; // 写进程的初始值为BUFFSIZE
            r_arg.val = 0; // 读进程的初始值为0
            lock.val = 1;
            // 第一个信号灯给写进程,第二个给读进程
            if (semctl(semid, 0, SETVAL, w_arg) == -1 || 
                semctl(semid, 1, SETVAL, r_arg) == -1 ||
                semctl(semid, 2, SETVAL, lock)  == -1) {
                perror("IPC error 1: semctl");
                exit(1);
            }
            int write_buff = fork();
            if (write_buff == 0) {
                // 写进程当中
                unsigned char c; // 暂时存储文件数据
                source_file = fopen(source, "r");
                long long * in_index = (long long *)shmat(in_index_id, NULL, SHM_W); // 用于标志写入的位置
                unsigned char * buffer = (unsigned char *)shmat(share_buffer, NULL, SHM_W);
                bool * finished = (bool *)shmat(finish_flag, NULL, SHM_W);

                if (fread(&c, 1, sizeof(unsigned char), source_file) <= 0) {
                    printf("文件为空\n");
                    exit(EXIT_SUCCESS);
                }
                while(true) {
                    P(semid, 0);
                    *(buffer + (*in_index) % BUFFSIZE) = c;
                    // printf("填入缓冲区%c, 此时in_index = %lld\n", c,  (*in_index));
                    
                    if (fread(&c, 1, sizeof(unsigned char), source_file) <= 0) {
                        printf("文件结束\n");
                        *finished = true;
                        V(semid, 1);
                        fclose(source_file);
                        break;
                    }
                    // sleep(0.1);
                    (*in_index)++;
                    (*in_index) %= BUFFSIZE;
                    V(semid, 1);
                }

            } else {
                int read_buff = fork();
                if (read_buff == 0) {
                    // 读进程
                    target_file = fopen(target, "w");
                    long long out_index = 0;
                    unsigned char * buffer = (unsigned char *)shmat(share_buffer, NULL, SHM_R);
                    bool * finished = (bool *)shmat(finish_flag, NULL, SHM_R);
                    long long * in_index = (long long *)shmat(in_index_id, NULL, SHM_R);
                    unsigned char c;
                    while (true)
                    {
                        P(semid, 1);
                        c = *(buffer + out_index % BUFFSIZE);
                        fwrite(&c,1, sizeof(unsigned char), target_file);
                        out_index++;
                        out_index %= BUFFSIZE;
                        // printf("写入文件%c, 此时out_index = %lld, in_index = %lld\n", c, out_index, *in_index);
                        V(semid, 0);
                        if ((*finished) && (out_index == ((*in_index) + 1) % BUFFSIZE)) {
                            fclose(target_file);
                            printf("文件结束啦");
                            exit(EXIT_SUCCESS);
                        }
                    }
                } else {
                    // 父进程
                    waitpid(write_buff, NULL, 0);
                    waitpid(read_buff, NULL, 0);
                    // 销毁信号灯
                    if (semctl(semid, 0, IPC_RMID) == -1) {
                        perror("Destroy Semaphore Failed!\n");
                    }
                    // 销毁共享内存
                    if (shmctl(share_buffer, IPC_RMID, NULL) == -1) {
                        perror("Destroy share memory failed!\n");
                    }
                }
            }

        } else {
            perror("IPC error2: semget");
            exit(1);
        }
    } else {
        perror("Semaphore is already created!\n");
        exit(1);
    }
    return 0;
}
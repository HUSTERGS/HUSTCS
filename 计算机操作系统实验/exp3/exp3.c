#include <sys/types.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <stdbool.h>

#define BUFFSIZE 100


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
    // 信号灯集
    int semid;
    // 创建共享分区，大小为buff
    int share_buffer = shmget(IPC_PRIVATE, sizeof(unsigned char) * BUFFSIZE, IPC_CREAT | 0666);
    // 先暂时这么写
    const char * source = "input.txt";
    const char * target = "output.txt";

    if ((semid = semget(IPC_PRIVATE, 0, 0) == -1)) {
        // 如果信号灯集不存在的话，就创建三个信号灯,第三个信号灯用于判断是否完成
        if ((semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666)) != -1) {
            // 如果创建成功
            union semun w_arg; // 用于写进程的参数
            union semun r_arg; // 用于读进程的参数
            // union semun lock;
            w_arg.val = BUFFSIZE; // 写进程的初始值为BUFFSIZE
            r_arg.val = 0; // 读进程的初始值为0
            // lock.val = 1;
            // 第一个信号灯给写进程,第二个给读进程
            if (semctl(semid, 0, SETVAL, w_arg) == -1 || 
                semctl(semid, 1, SETVAL, r_arg) == -1) {
                perror("IPC error 1: semctl");
                exit(1);
            }
            int write_buff = fork();
            if (write_buff == 0) {
                // unsigned long * file_len_tmp = (unsigned long *)shmat(file_len_share, NULL, SHM_W);
                unsigned long counter;
                unsigned char c;
                unsigned long file_len;
                // int * in_index = (int *)shmat(in_index, NULL, SHM_W);
                int in_index = 0;
                FILE * source_file = fopen(source, "rb");

                unsigned char * buffer = (unsigned char *)shmat(share_buffer, NULL, 0);
                // printf("进入写入方\n");
                fseek(source_file,0,SEEK_END);
                // printf("获取文件长度\n");
                // *file_len_tmp = ftell(source_file); // 获取文件长度
                file_len = ftell(source_file);
                // printf("写入方得到的文件长度为%ld", file_len);
               
                fseek(source_file, 0, SEEK_SET);

                for (counter = 0; counter < file_len; counter++) {
                    c = fgetc(source_file);
                    P(semid, 0);
                    *(buffer + (in_index % BUFFSIZE)) = c;
                    in_index++;
                    in_index %= BUFFSIZE;
                    V(semid, 1);
                    // printf("从文件读出%c, counter = %ld, file_len = %ld\n", c, counter, file_len);
                }
                printf("写入进程结束\n");

            } else {
                int read_buff = fork();
                if (read_buff == 0) {
                    // 读进程
                    // printf("进入读进程\n");
                    unsigned char c;
                    FILE * target_file = fopen(target, "wb");
                    FILE * source_file = fopen(source, "rb");
                    fseek(target_file, 0, SEEK_SET);
                    int out_index = 0;
                    unsigned char * buffer = (unsigned char *)shmat(share_buffer, NULL, 0);
                    // printf("读进程尝试获取长度\n");
                    fseek(source_file,0,SEEK_END);
                    // printf("读进程获取文件长度\n");
                    unsigned long file_len = ftell(source_file);
                    // printf("获取长度成功\n");
                    fclose(source_file);
                    // printf("读取方得到的文件长度为%ld", file_len);
                    unsigned long counter;  
                    for (counter = 0; counter < file_len; counter++) {
                        P(semid, 1);
                        c = *(buffer + out_index % BUFFSIZE);
                        out_index++;
                        out_index %= BUFFSIZE;
                        fputc(c, target_file);
                        V(semid, 0);
                        // printf("写入文件%c, counter = %ld length = %ld\n", c,counter,  file_len);
                    }
                    printf("读出进程结束\n");
                } else {
                    // 父进程
                    waitpid(read_buff, NULL, 0);
                    waitpid(write_buff, NULL, 0);
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
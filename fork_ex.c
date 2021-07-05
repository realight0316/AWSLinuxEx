#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // pid_t 프로세서 아이디 값 저장 processor id value save
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFF_SIZE 1024

int main(){
    int status;
    int i = 3;
    pid_t pid;
    char buff[BUFF_SIZE];
    int rdByte;

    // file descriptor table
    // 0:stdin, 1:stdout 2:stderr
    // 3에 할당
    int fd = open("a.txt", O_RDONLY);

    if(fd<0){
        printf("Cannot open");
        return 0;
    }
    pid = fork();

    // fork가 정상적으로 실행되지 않은 경우(예외 등록)
    if(pid<0){
        printf("Cannot create child process\n");
        return 0;
    }

    // 부모 프로세스
    else if(pid>0){
        printf("부모프로세스 %d : %d\n", getpid(), pid);
        printf("i=%d\n", i);
        rdByte = read(fd, buff, BUFF_SIZE);
        //wait(&status); // 부모가 자식프로세스 보다 먼저 종료되면 안됨

        if(rdByte<0)
            printf("Cannot read file\n");
        else
        printf("read : %s\n",buff);
    }
    // 자식 프로세스
    else if(pid==0){
        printf("자식프로세스 %d\n", getpid());
        printf("i=%d\n", i);

        rdByte = read(fd, buff, BUFF_SIZE);
        if(rdByte<0)
            printf("Cannot read file\n");
        else
        printf("read : %s\n",buff);
    }

    return 0;
}
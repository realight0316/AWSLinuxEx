#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // pid_t 프로세서 아이디 값 저장 processor id value save
#include <sys/types.h> // wait
#include <sys/wait.h> //wait
#include <fcntl.h> //open, read

int main(void){
    int status;
    pid_t pid;
    pid = fork();
    int result;

    //fork가 정상적으로 실행되지 않았음
    if(pid<0){
        printf("Cannot create process\n");
        return -1;
    }
    //부모프로세스의 경우
    else if(pid>0){
        printf("부모프로세스 : 자식PID = %d\n", pid);
    }
    //자식프로세스의 경우
    else{
        printf("자식프로세스 : 내 PID = %d\n", getpid());
        // execl("/bin/ls", "ls", "-al", NULL);
        // execl("/bin/test", "test", NULL);
        execl("/usr/bin/python", "python", "hellotest.py", NULL);
    }
    wait(&status);
    return 0;
}
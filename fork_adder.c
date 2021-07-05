#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // pid_t 프로세서 아이디 값 저장 processor id value save
#include <sys/types.h> // wait
#include <sys/wait.h> //wait
#include <fcntl.h> //open, read

int adder(int start, int end){
    int i = 0;
    int result = 0;
    for (i = start; i < end+1; i++){
        result += i;
    }
    return result;
}

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
        result = adder(1,100000);
        printf("부모proc의 result = %d\n", result);
    }
    //자식프로세스의 경우
    else{
        printf("자식프로세스 : 내 PID = %d\n", getpid());
        result = adder(100001,200000);
        printf("자식proc의 result = %d\n", result);
    }
    wait(&status);
    return 0;
}
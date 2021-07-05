#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

void pr_exit(int status){
 //1. 정상종료, 2. 시그널에 의해 종료 3. 시그널에 의한 정지
    if(WIFEXITED(status)){
        printf("정상적인 종료, 종료조건 %d\n", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
        printf("시그널에 의해서 종료 %d %s\n",WTERMSIG(status), WCOREDUMP(status) ? "core file generated" : "");
    }
    else{

    }
}

int main(void){
    pid_t pid;
    int status;
    int fd;

    /*
    fd = open("aaa.txt", O_RDONLY);
    if(fd<0){
        // stderr -> 메세지 전달
        perror("Cannot open file");
    }
    */

    pid = fork();

    // 정상적으로 fork가 실행되지 않았을때, 자식프로세스 미생성
    if(pid<0){
        // stderr -> 메세지 전달
        perror("fork error");
    }
    // 부모프로세스 실행
    else if(pid>0){
    
    }
    // 자식프로세스 실행
    else{
        if(wait(status)==pid){
            perror("");
            exit(7);
        }
    }

    if(wait(&status)==pid){
        pr_exit(status);
    }else if(pid==0){
        abort();
    }
//wait이 호출되면 status변수에 주소값 전달하면 종료조건을 적어줌

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // pid_t 프로세서 아이디 값 저장 processor id value save
#include <sys/types.h> // wait
#include <sys/wait.h> //wait
#include <fcntl.h> //open, read

int adder (int a, int b){

}
int global = 10;

int main(){
    int i = 20;
    pid_t pid;
    int status;

    pid = fork();

    if(pid==0){
        global = global + 10;
        i = i + 10;
    }
    else{
        global = global + 100;
        i = i + 100;
        wait(&status);
    }
    printf("global : %d, i : %d\n",global, i);
}
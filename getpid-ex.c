#include <stdio.h>
#include <unistd.h>

int main(void){
    pid_t pid, ppid;
    pid = getpid(); //process id value
    ppid = getppid();
    printf("my pid is %d\n", pid);
    printf("my ppid is %d\n", ppid);
    sleep(10); // wait 10sec
}
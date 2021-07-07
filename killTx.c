#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// 첫번째에 signal[번호], [pid]
// argc =3 / argv[1] =signal num / argv[2] =pid / "--help": 사용법 안내

// 예시)) ./killTx 2 0000 = 프로세서 주소 0000에 2(SIGINT=ctrl+C)를 보내라
int main(int argc, char *argv[]){

    int result;
    int sigNum;
    pid_t pid;

    if(argc!=3 || strcmp(argv[1], "--help")==0)
        printf("%s pid sig-num\n", argv[0]);

    // pid를 숫자로 변환
    sigNum = atoi(argv[1]);
    pid    = atoi(argv[2]);

    // 내가 보내고자하는 프로세스에게 signal을 전달(=발생)
    result = kill(pid, sigNum);
    if(result!=0)
        printf("Error: system call kill()\n");
    else
        printf("signal 정상 작동\n");
    


}
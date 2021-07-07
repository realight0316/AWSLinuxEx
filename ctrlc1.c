#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigHandler(int sig){
    printf("\n시그널 보내 시그널 보내(찌릿찌릿 찌릿찌릿): %d\n", sig);
    (void)signal(SIGINT, SIG_DFL);
    // SIGINT가 들어오면 원래 시스템핸들러(디폴트 설정값)으로 돌아간다. -처음엔 정상 출력 / 두번째는 종료
}

int main(void){
    // signal을 활용하기 위해 핸들러 정의

    // SIGINT라는 시그널이 들어오면 sigHandler로 이동하라 / 커널에 등록
    signal(SIGINT, sigHandler);

    while(1){
        printf("Hello World!\n");
        sleep(10);
        // 시그널이 들어오면 10초를 쉬지않고 프린트 출력을 진행해버림
    }
}
#include "msgheader.h"

//수신부
int main(){
    //구조체 객체선언
    struct my_msg_st some_data;
    int msgid;
    // 전송할 데이터 확인
    int running = 1;
    char buffer[BUFSIZ];

    // 1. 메세지큐 생성
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    // 메세지 큐가 생성되지 않았을 때
    if(msgid==-1){
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    while(running){
        // 정상적으로 메세지큐를 읽지 못했을때
        if(msgrcv(msgid, (void*)&some_data, BUFSIZ, 0, 0)==-1){
            fprintf(stderr,"msgrcv failed with error: %d\n", errno);
            exit(EXIT_SUCCESS);
        }
        printf("Receive: %s", some_data.some_text);

        if (strncmp(some_data.some_text,"end",3)==0){
            running=0;
        }
    }
    // 수신부에서 메세지 삭제
    if(msgctl(msgid, IPC_RMID, 0)==-1){
        fprintf(stderr,"msgctl(IPC_RMID) failed:%d\n", errno);
        exit(EXIT_FAILURE);

    }
    exit(EXIT_SUCCESS);
}
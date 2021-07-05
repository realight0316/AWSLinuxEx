#include "msgheader.h"

//송신부
int main(){
    //구조체 객체선언
    struct my_msg_st some_data;
    int msgid;
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
        printf("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin);
        some_data.my_msg_type=1;
        strcpy(some_data.some_text, buffer);

    // 2. 메세지 큐에 보내기
        // msgsnd의 리턴이 -1이면 정상전송된 것이 아님
        if(msgsnd(msgid,(void*)&some_data, MAX_TEXT, 0)==-1){
        // (*void) 오직 주소값만(API에서 지정)
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp(buffer,"end",3)==0){
            running = 0;
        }
    }
    exit(EXIT_SUCCESS);
}
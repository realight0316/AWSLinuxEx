#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

int main(){
    time_t UTCtime;
    struct tm *tm;

    char buf[BUFSIZ];
    // 문자열로 시간 정보를 저장할 버퍼
    
    time(&UTCtime); 
    // 커널에서 시간정보 받아서 해당 변수에 넣어줌

    printf("time : %u\n", (unsigned)UTCtime); 
    // 현재 시간 출력 [ex) time : 1625703847]

    tm = localtime(&UTCtime);
    printf("asctime : %s\n",asctime(tm));
    //현재 시간을 tm 구조체로 출력 [ex) asctime : Thu Jul  8 09:29:37 2021]

    // 1. 사용자가 만든 문자열 저장버퍼
    // 2. 버퍼 사이즈
    // 3. 시간표기형식 사용자 설정 / 소문자는 간결, 대문자는 전부표기를 의미 (연-월-일(요일) 시:분:초)
    // 4. 시간정보를 받아오는 곳
    strftime(buf, sizeof(buf), "%y-%m-%d(%a) %H:%M:%S", tm);
    printf("My time: %s\n",buf);
    // [ex) My time: 21-07-08(Thu) 09:43:23]
}
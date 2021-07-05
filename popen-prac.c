#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    FILE *read_fp;
    int chars_read;
    char buffer[BUFSIZ +1]; //초기화X
    // printf("BUFSIZE = %d\n", BUFSIZ);

    // 버퍼를 사이즈만큼 '\0'으로 초기화
    memset(buffer, '\0', sizeof(buffer));
    // popen -> 터미널 프로세스 + "ls -al", 이후 출력되는 문자열을 real_fp로 리턴
    read_fp = popen("ls -al", "r");

    // 정상 작동 시
    if(read_fp!=NULL){
        // 한 바이트 단위(sizeof(char))로 buffer에 저장, 최대 BUFSIZ만큼, read_fp로부터 읽어들임
        chars_read = fread(buffer,sizeof(char),BUFSIZ,read_fp);
        
        if(chars_read>0){
            printf("out: \n%s\n", buffer);
        }

        pclose(read_fp);
        exit(0);
    }
    
}
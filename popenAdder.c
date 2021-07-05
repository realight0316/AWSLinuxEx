#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long add1num(int start, int end);

int main(){
    FILE *read_fp;
    long int chars_read;
    long int add2num = 0;
    long int finalval;
    char buffer[BUFSIZ +1]; //초기화X
    // printf("BUFSIZE = %d\n", BUFSIZ);

    // 버퍼를 사이즈만큼 '\0'으로 초기화
    memset(buffer, '\0', sizeof(buffer));
    // popen -> 터미널 프로세스 + "ls -al", 이후 출력되는 문자열을 real_fp로 리턴
    read_fp = popen("./20000adder", "r");

    // 정상 작동 시
    if(read_fp!=NULL){
        // 한 바이트 단위(sizeof(char))로 buffer에 저장, 최대 BUFSIZ만큼, read_fp로부터 읽어들임
        chars_read = fread(buffer,sizeof(char),BUFSIZ,read_fp);
        add2num = atol(chars_read);
        finalval = add1num(1,100000) + add2num;

        printf("결과값: %ld", finalval);
        pclose(read_fp);
        exit(0);
    }
    
}
long add1num(int start, int end){
    long int val = 0;
    for(int i=start;i<=end;i++){
        val += i; 
    }
    return val;
}
#include <stdlib.h>
#include <stdio.h>

int main(void){
    printf("Running ps with system\n");
    system("ls -al");   // 코드 내에서 터미널명령어 사용
    system("./arg_p 1234 abcd &");    // 코드 내에서 터미널명령어 사용
    printf("precess is done\n\n");

    exit(0);
}
#include <stdio.h>
#include <fcntl.h>

int main(void){
    int fd;
    int i =3;
    while(1){
    fd = open("/home/bit/AWSLinuxEx/a.txt",O_RDONLY,O_TRUNC);
    printf("%d번째 파일디스크립터 넘버=%d\n",i,fd);
    i++;
    if(fd==-1)
        break;
    }
    return 0;
}
#include <stdio.h>

int main(){
    long sum = 0;

    for(int i = 100001;i<=200000;i++){
        sum += i;
    }
    printf("%ld\n", sum);
    return 0;
}
#include <stdio.h>
int main(){
    unsigned a;
    char b[4] = {1, 2, 3, 4};
    a = (b[0]) | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
    printf("%x\n", a);
    a = (a << 16) >> 16;
    printf("%x\n", a);
    return 0;
}
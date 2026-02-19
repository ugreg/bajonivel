/*
 * suppress mac os only linker warnings clang: warning: overriding 
 * deployment version from '16.0' to '26.0' [-Woverriding-deployment-version]
 * 
 * gcc-14 ./Rama.c -o app -mmacosx-version-min='26.0'
 * 
 */

#include <stdio.h>

int main() {
    printf("Welcome to Zero2Hero C Programming!");
    return 0;
}

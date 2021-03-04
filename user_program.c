#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>


void main(){
        unsigned long int result[1024];

        int i;
        syscall(355,768,1023,result);
        for(i=768;i<=1023;i++){
                printf("[entry %d : %lx]\n",i,result[i]);
        }
}       

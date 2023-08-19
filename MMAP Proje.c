#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0

struct shared{                                                             /*Gerekli structer yapısı*/
    int data;                                                              /*Paylaşılacak data*/
    int flag[2];                                                           /*Peterson Solution için flag*/ 
    int turn;                                                              /*Peterson Solution için turn*/
};

struct shared *foo;                                                        /*Variable*/


void process1(){                                                           /*Okuma Prosesi*/
     int i=0;
        while(i<101){

            foo->flag[0] = TRUE;
            foo->turn = 1;
            while(foo->flag[0] == TRUE && foo->turn == 1){                 /*Peterson Solution kritik bölge*/
                

            };
            printf("PID = %d--Yazılan Data = %d\n",getppid(), foo->data);
            foo->data++;
            i++;
            foo->flag[0] = FALSE;
        }

}


void process2(){                                                           /*Okuma Prosesi*/
    int i=0;
        while(i<101){

            foo->flag[1] = TRUE;
            foo->turn = 0;
            while(foo->flag[1] == TRUE && foo->turn == 0){                 /*Peterson Solution kritik bölge*/

            };
            
            printf("PID = %d--Okunan Data = %d\n",getppid(), foo->data);
            i++;
            foo->flag[1] = FALSE;
        }

}

int main(){

    foo = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE,                    /*Memory mapping*/
                        MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    pid_t child;

    if((child=fork())==0){                                                 /*Child Process oluşturma*/
        process1();
    }

    else{
        process2();
    }
    munmap(foo,sizeof(int));
    return 0;
}


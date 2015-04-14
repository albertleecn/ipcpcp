//
//  main.c
//  ipcpcp
//
//  Created by albert on 15/4/14.
//  Copyright (c) 2015 albert. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define ThreadCnt 5

typedef struct ST_THREAD_ARG{
    pthread_t* ptid;
    int id;
} THREAD_ARG;

void* thread_work(void* arg);

/*
 * main function
 */
int main(int argc, const char * argv[]) {
    int i;
    pthread_t threadArray[ThreadCnt];
    THREAD_ARG threadArg[ThreadCnt];
    //
    srand((int)time(0));

    printf("Begin:Producer and Consumer Problem\n");
    
    for (i=0;i<ThreadCnt;i++)
    {
        threadArg[i].ptid=&threadArray[i];
        threadArg[i].id=i;
        printf("Creating the %dth Thread",threadArg[i].id);
        pthread_create(&threadArray[i], NULL, thread_work, (void*)&threadArg[i]);
        printf("(%u)\n",(unsigned int)threadArray[i]);
    }
    for (i=0;i<ThreadCnt;i++)
    {
        pthread_join(threadArray[i], NULL);
    }
    printf("End:Producer and Consumer Problem\n");
    return 0;
}

/*
 * thread_work function
 */
void* thread_work(void* arg)
{
    THREAD_ARG* parg=(THREAD_ARG*)arg;
    
    sleep(parg->id * (rand() % 5));
    printf("hi, I am the %dth thread(%u)\n",parg->id,(unsigned int)parg->ptid);
    pthread_exit(NULL);
}

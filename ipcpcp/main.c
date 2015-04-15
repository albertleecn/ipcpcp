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

#define ThreadCnt 3
#define ItemsBufferSize 5

///
typedef struct ST_THREAD_ARG{
    pthread_t* ptid;
    int id;
} THREAD_ARG;

///
typedef struct ST_ITEM{
    int id;
    int producerId;
    time_t createTime;
} ITEM;

///global Items Buffer
ITEM gItemsBuf[ItemsBufferSize];
///
pthread_mutex_t mutexItemsBuf = PTHREAD_MUTEX_INITIALIZER;

///
void* thread_producer_work(void* arg);
void initializeItemsBuf();
void displayItemInfo(int aIndex, ITEM* aItem);

/*
 * main function
 */
int main(int argc, const char * argv[]) {
    int i;
    pthread_t threadArray[ThreadCnt];
    THREAD_ARG threadArg[ThreadCnt];

    printf("Begin:Producer and Consumer Problem\n");
    ///
    srand((int)time(0));
    ///
    initializeItemsBuf();
    ///
    for (i=0;i<ThreadCnt;i++)
    {
        threadArg[i].ptid=&threadArray[i];
        threadArg[i].id=i+1;
        printf("Creating the %dth Thread",threadArg[i].id);
        pthread_create(&threadArray[i], NULL, thread_producer_work, (void*)&threadArg[i]);
        printf("(%u)\n",(unsigned int)threadArray[i]);
    }
    ///
    for (i=0;i<ThreadCnt;i++)
    {
        pthread_join(threadArray[i], NULL);
    }
    
    ///
    for (i=0;i<ItemsBufferSize;i++)
    {
        displayItemInfo(i,&gItemsBuf[i]);
    }
    
    
    printf("End:Producer and Consumer Problem\n");
    return 0;
}

/*
 *
 */
void displayItemInfo(int aIndex, ITEM* aItem)
{
    if (aIndex>=0)
    {
        printf("%d:id=%d,producerId=%d,time=%s"
               ,aIndex,
               aItem->id
               ,aItem->producerId
               ,asctime(gmtime(&aItem->createTime)));
    }
    else
    {
        printf("id=%d,producerId=%d,time=%s"
               ,aItem->id
               ,aItem->producerId
               ,asctime(gmtime(&aItem->createTime)));
    }
}

/*
 * thread_producer_work function
 */
void* thread_producer_work(void* arg)
{
    THREAD_ARG* parg=(THREAD_ARG*)arg;
    int i;
    int j;
    int currTotal;
    int isFound=0;
    
    sleep(parg->id * (rand() % 5));
    printf("hi, I am the %dth thread(%u)\n",parg->id,(unsigned int)parg->ptid);
    while (1) {
        printf("the %dth thread is entering critical region...\n",parg->id);
        ///
        pthread_mutex_lock(&mutexItemsBuf);
        printf("the %dth thread enters critical region\n",parg->id);
        //////do real work
        currTotal=0;
        for (i=0;i<ItemsBufferSize;i++)
        {
            if (gItemsBuf[i].id!=-1)
            {
                currTotal=currTotal+1;
            }
        }
        ///
        sleep(1+parg->id * (rand() % 10));
        ///
        if (currTotal<ItemsBufferSize)
        {
            currTotal=currTotal+1;
            j=rand()%ItemsBufferSize;
            isFound=0;
            for (i=j;i<ItemsBufferSize;i++)
            {
                if (gItemsBuf[i].id==-1)
                {
                    isFound=1;
                    gItemsBuf[i].id=currTotal;
                    gItemsBuf[i].producerId=parg->id;
                    gItemsBuf[i].createTime=time(NULL);
                    displayItemInfo(i,&gItemsBuf[i]);
                    break;
                }
            }
            if (isFound==0)
            {
                for (i=0;i<j;i++)
                {
                    if (gItemsBuf[i].id==-1)
                    {
                        isFound=1;
                        gItemsBuf[i].id=currTotal;
                        gItemsBuf[i].producerId=parg->id;
                        gItemsBuf[i].createTime=time(NULL);
                        displayItemInfo(i,&gItemsBuf[i]);
                        break;
                    }
                }
            }
        }
        
        ///
        printf("the %dth thread is leaving critical region...\n",parg->id);
        pthread_mutex_unlock(&mutexItemsBuf);
        printf("the %dth thread leaves critical region!\n",parg->id);
        if (currTotal>=ItemsBufferSize)
        {
            break;
        }
    }
    printf("the %dth thread exit.\n",parg->id);
    pthread_exit(NULL);
}

/*
 * initialize global ItemsBuf
 */
void initializeItemsBuf()
{
    int i ;
    for (i=0;i<ItemsBufferSize;i++)
    {
        gItemsBuf[i].id=-1;
        gItemsBuf[i].producerId=-1;
        gItemsBuf[i].createTime=time(NULL);
    }
    
}

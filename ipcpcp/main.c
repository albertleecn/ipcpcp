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
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define ThreadProducerCnt 4
#define ThreadComsumerCnt 5
#define ItemsBufferSize 3
#define ItemsCnt 10

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

///
typedef struct ST_ITEMBUF{
    ///global Items Buffer
    ITEM Buffer[ItemsBufferSize];
    ///
    int itemsProduceTotal;
    ///
    int itemsComsumeTotal;
    ///
    pthread_mutex_t mutex;
    ///
    sem_t* psemFull;
    sem_t* psemEmpty;
}ITEMBUF;

///
char semFull_Name[]="IPC_PCPFULL10";
char semEmpty_Name[]="IPC_PCPEMPTY10";
///
ITEMBUF gBuffer;
pthread_t threadProducerArray[ThreadProducerCnt];
THREAD_ARG threadProducerArg[ThreadProducerCnt];
pthread_t threadComsumerArray[ThreadComsumerCnt];
THREAD_ARG threadComsumerArg[ThreadComsumerCnt];

///
int getFreeItemIndex();
int getFullItemIndex();
void* thread_producer_work(void* arg);
void* thread_comsumer_work(void* arg);
void initializeItemsBuf();
void initializeThreads();
void finializeItemsBuf();
void finializeThreads();
void displayItemInfo(int aIndex, ITEM* aItem);
void displayItemsBuf();



/*
 * main function
 */
int main(int argc, const char * argv[]) {
    ///
    printf("Begin:Producer and Consumer Problem\n");
    ///
    srand((int)time(0));
    initializeItemsBuf();
    displayItemsBuf();
    initializeThreads();
    ///
    finializeThreads();
    finializeItemsBuf();
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
 *
 */
void displayItemsBuf()
{
    int i;
    /*
    for (i=0;i<ItemsBufferSize;i++)
    {
        displayItemInfo(i,&gBuffer.Buffer[i]);
    }
    */
    
    for (i=0;i<ItemsBufferSize;i++)
    {
        printf("%4d",i);
    }
    printf("\n");
    for (i=0;i<ItemsBufferSize;i++)
    {
        if (gBuffer.Buffer[i].id>-1)
        {
            printf("%4d",gBuffer.Buffer[i].id);
        }
        else
        {
            printf("   *");
        }
            
    }
    printf("\n");
    
    
}

/*
 *
 */
void initializeThreads()
{
    int i;
    
    for (i=0;i<ThreadComsumerCnt;i++)
    {
        threadComsumerArg[i].ptid=&threadComsumerArray[i];
        threadComsumerArg[i].id=i+1;
        printf("Creating the %dth Comsumer Thread",threadComsumerArg[i].id);
        pthread_create(&threadComsumerArray[i], NULL, thread_comsumer_work, (void*)&threadComsumerArg[i]);
        printf("(%u)\n",(unsigned int)threadComsumerArray[i]);
    }

    for (i=0;i<ThreadProducerCnt;i++)
    {
        threadProducerArg[i].ptid=&threadProducerArray[i];
        threadProducerArg[i].id=i+11;
        printf("Creating the %dth Producer Thread",threadProducerArg[i].id);
        pthread_create(&threadProducerArray[i], NULL, thread_producer_work, (void*)&threadProducerArg[i]);
        printf("(%u)\n",(unsigned int)threadProducerArray[i]);
    }
}

/*
 *
 */
void finializeThreads()
{
    int i;

    for (i=0;i<ThreadComsumerCnt;i++)
    {
        pthread_join(threadComsumerArray[i], NULL);
    }
    
    for (i=0;i<ThreadProducerCnt;i++)
    {
        pthread_join(threadProducerArray[i], NULL);
    }
}

/*
 *
 */
int getFreeItemIndex()
{
    int i;
    int j;
    int index;
    j=rand()%ItemsBufferSize;
    index=-1;
    for (i=j;i<ItemsBufferSize;i++)
    {
        if (gBuffer.Buffer[i].id==-1)
        {
            index=i;
            break;
        }
    }
    if (index==-1)
    {
        for (i=0;i<j;i++)
        {
            if (gBuffer.Buffer[i].id==-1)
            {
                index=i;
                break;
            }
        }
    }
    return index;
}

/*
 *
 */
int getFullItemIndex()
{
    int i;
    int j;
    int index;
    j=rand()%ItemsBufferSize;
    index=-1;
    for (i=j;i<ItemsBufferSize;i++)
    {
        if (gBuffer.Buffer[i].id>-1)
        {
            index=i;
            break;
        }
    }
    if (index==-1)
    {
        for (i=0;i<j;i++)
        {
            if (gBuffer.Buffer[i].id>-1)
            {
                index=i;
                break;
            }
        }
    }
    return index;
}

/*
 * thread_producer_work function
 */
void* thread_producer_work(void* arg)
{
    THREAD_ARG* parg=(THREAD_ARG*)arg;
    int i;
    int currTotal;
    int isContinue;
    
    sleep(1+ rand() % 2);
    ////false
    isContinue=0;
    printf("hi, I am the %dth producer thread(%u)\n",parg->id,(unsigned int)(*(pthread_t*)parg->ptid));
    while (1) {
        //////
        isContinue=0;
        pthread_mutex_lock(&gBuffer.mutex);
        currTotal=gBuffer.itemsProduceTotal;
        if (currTotal<ItemsCnt)
        {
            isContinue=1;
            currTotal=currTotal+1;
            gBuffer.itemsProduceTotal=currTotal;
        }
        pthread_mutex_unlock(&gBuffer.mutex);
        
        //////
        if (isContinue==0)
        {
            break;
        }
        
        
        //////
        sem_wait(gBuffer.psemEmpty);
        //printf("the %dth producer thread is entering critical region...\n",parg->id);
        ///
        pthread_mutex_lock(&gBuffer.mutex);
        printf("the %dth producer thread enters critical region\n",parg->id);
        
        //////do real work
        ///
        displayItemsBuf();
        sleep(1+ rand() % 2);
        i=getFreeItemIndex();
        if (i>=0)
        {
            gBuffer.Buffer[i].id=currTotal;
            gBuffer.Buffer[i].producerId=parg->id;
            gBuffer.Buffer[i].createTime=time(NULL);
            printf("thread(%d) produces:",parg->id);
            displayItemInfo(i,&gBuffer.Buffer[i]);
        }
        displayItemsBuf();
        
        ///
        printf("the %dth producer thread leaves critical region!\n",parg->id);
        pthread_mutex_unlock(&gBuffer.mutex);
        sem_post(gBuffer.psemFull);
    }
    
    //////
    printf("the %dth producer thread exit.\n",parg->id);
    pthread_exit(NULL);
}

/*
 * thread_comsumer_work function
 */
void* thread_comsumer_work(void* arg)
{
    THREAD_ARG* parg=(THREAD_ARG*)arg;
    int i;
    int currTotal;
    ITEM mITEM;
    int isContinue;
    
    sleep(1+ rand() % 3);
    ////false
    isContinue=0;
    printf("hi, I am the %dth comsumer thread(%u)\n",parg->id,(unsigned int)(*(pthread_t*)parg->ptid));
    while (1) {
        //////
        isContinue=0;
        pthread_mutex_lock(&gBuffer.mutex);
        currTotal=gBuffer.itemsComsumeTotal;
        if (currTotal<ItemsCnt)
        {
            isContinue=1;
            currTotal=currTotal+1;
            gBuffer.itemsComsumeTotal=currTotal;
        }
        pthread_mutex_unlock(&gBuffer.mutex);
        
        //////
        if (isContinue==0)
        {
            break;
        }
        

        //////
        sem_wait(gBuffer.psemFull);
        //printf("the %dth comsumer thread is entering critical region...\n",parg->id);
        ///
        pthread_mutex_lock(&gBuffer.mutex);
        printf("the %dth comsumer thread enters critical region\n",parg->id);
        
        //////do real work
        ///
        displayItemsBuf();
        sleep(1+ rand() % 2);
        i=getFullItemIndex();
        if (i>=0)
        {
            displayItemInfo(i,&gBuffer.Buffer[i]);
            mITEM.id=gBuffer.Buffer[i].id;
            mITEM.producerId=gBuffer.Buffer[i].producerId;
            mITEM.createTime=gBuffer.Buffer[i].createTime;
            gBuffer.Buffer[i].id=-1;
            gBuffer.Buffer[i].producerId=-1;
            gBuffer.Buffer[i].createTime=time(NULL);
            printf("thread(%d) comsumes:",parg->id);
            displayItemInfo(-1,&mITEM);
        }
        displayItemsBuf();
        
        ///
        printf("the %dth comsumer thread leaves critical region!\n",parg->id);
        pthread_mutex_unlock(&gBuffer.mutex);
        sem_post(gBuffer.psemEmpty);
    }
    printf("the %dth comsumer thread exit.\n",parg->id);
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
        gBuffer.Buffer[i].id=-1;
        gBuffer.Buffer[i].producerId=-1;
        gBuffer.Buffer[i].createTime=time(NULL);
    }
    pthread_mutex_init(&gBuffer.mutex, NULL);
    gBuffer.psemFull=sem_open(semFull_Name,O_CREAT|O_EXCL,S_IRUSR | S_IWUSR ,0);
    gBuffer.psemEmpty=sem_open(semEmpty_Name,O_CREAT|O_EXCL,S_IRUSR | S_IWUSR ,ItemsBufferSize);
    gBuffer.itemsProduceTotal=0;
    gBuffer.itemsComsumeTotal=0;
}

void finializeItemsBuf()
{
    if (gBuffer.psemFull!=NULL)
    {
        sem_close(gBuffer.psemFull);
        sem_unlink(semFull_Name);
    }
    if (gBuffer.psemEmpty!=NULL)
    {
        sem_close(gBuffer.psemEmpty);
        sem_unlink(semEmpty_Name);
    }
}

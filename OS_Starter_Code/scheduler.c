#include "headers.h"

//data
#define hpf_Algo 1
#define strn_Algo 2
#define rr_Algo 3
char Algo;
int time_quantum;
struct PCB recievedProcess;

//functions
void HPF();
void STRN();
void RR();
void IPC();

struct msgBuff
{
    long mtype;
    struct PCB process;
};
int main(int argc, char * argv[])
{
    initClk();
    Algo=argv[1][0]-'0';
    time_quantum=argv[2][0]-'0';
    printf("scheduler Arguments %d    %d\n",Algo, time_quantum);
    IPC();
    switch (Algo)
    {
    case hpf_Algo:
        HPF();
        break; 
    case strn_Algo:
        STRN();
        break;
    case rr_Algo:
        RR();
        break;
    }
    
    //TODO implement the scheduler :)
    //upon termination release the clock resources
    //destroyClk(true);
}

void IPC()
{
    int upQId = msgget(1234, 0666 | IPC_CREAT);
    if (upQId == -1){
        perror("error in creat");
        exit(-1);
    }
    struct msgBuff processInfo;
    int val = msgrcv(upQId, &processInfo, sizeof(processInfo.process), 0, !IPC_NOWAIT);
    if (val == -1)
        printf("Error in recieve");
    CopyPCB(&recievedProcess,processInfo.process);
    printf("The id is %d\n",recievedProcess.id);
     printf("The id is %d\n",processInfo.process.id);
}

void HPF()  // check the return type of the alogrithms
{
    printf("The user chose to run HPF\n");
}
void STRN()
{
    printf("The user chose to run STRN\n");
}
void RR()
{
    //printf("The user chose to run RR\n");


    // for trying the *****************************
    struct PCB arr[5];
    setPCB(&arr[0],1,1,5,1);
    setPCB(&arr[1],2,1,3,1);
    setPCB(&arr[2],3,1,2,1);
    setPCB(&arr[3],4,1,6,1);
    setPCB(&arr[4],5,1,3,1);

    /*struct PCBNode ARR[5];
    ARR[0] = GenerateNode(arr[0]);
    ARR[1] = GenerateNode(arr[1]);
    ARR[2] = GenerateNode(arr[2]);
    ARR[3] = GenerateNode(arr[3]);
    ARR[4] = GenerateNode(arr[4]);*/

    struct PriorityQueue que;
    initializeQueue(&que);
    /*enQueue(&que,&ARR[0]);
    enQueue(&que,&ARR[1]);
    enQueue(&que,&ARR[2]);
    enQueue(&que,&ARR[3]);
    enQueue(&que,&ARR[4]);*/
    Add(&que,arr[0]);
    Add(&que,arr[1]);
    Add(&que,arr[2]);
    Add(&que,arr[3]);
    Add(&que,arr[4]);

    struct PCB next;

    DeQueue(&que,&next);
    printf("%d\t",next.id);
    DeQueue(&que,&next);
    printf("%d\t",next.id);
    DeQueue(&que,&next);
    printf("%d\t",next.id);
    DeQueue(&que,&next);
    printf("%d\t",next.id);
    DeQueue(&que,&next);
    printf("%d\t",next.id);
    printf("\n");

    /*next = que.head->pcb;
    if(next.state == NotStarted)
    {
        int process = fork();
        if(process == -1)
        {
            printf("error in forking\n");
        }
        else if(process == 0)
        {
            char sendid = next.id + '0';
            char * sendingid = &sendid;
            char* argv[] = {"./process.out", sendingid,0};
            execve(argv[0], &argv[0], NULL);
        }
    }*/


    //*********************************************

}
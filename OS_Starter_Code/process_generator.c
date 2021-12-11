#include "headers.h"


//variables 
int Algo; 
int time_quantum;

//temp for input
int a,b,c,d;
struct PCB processToBeSent;
struct PriorityQueue que;
//functions
void clearResources(int);
void getAlgorithm();
void Start_Clk_Scheduler();
void ReadFile();
void IPC();

struct msgBuff
{
    long mtype;
    struct PCB process;
};

int main(int argc, char * argv[])
{
    signal(SIGINT, clearResources);
    // TODO Initialization
    // 1. Read the input files.
    ReadFile();
    // 2. Ask the user for the chosen scheduling algorithm and its parameters, if there are any.

    while(que.head != NULL)
    {
        DeQueue(&que,&processToBeSent);
        printf("id %d, Arr time %d, Running time %d, Priority %d \n", processToBeSent.id, processToBeSent.ArrTime, processToBeSent.RunTime, processToBeSent.Priority);
    }

    getAlgorithm();   
    // 3. Initiate and create the scheduler and clock processes.
    Start_Clk_Scheduler();
    // 4. Use this function after creating the clock process to initialize clock
    initClk();
    IPC();
    // To get time use this
    //sleep(10);
    int x = getClk();
    printf("current time is %d\n", x);

       
    // TODO Generation Main Loop
    // 5. Create a data structure for processes and provide it with its parameters.
    // 6. Send the information to the scheduler at the appropriate time.
    // 7. Clear clock resources
    while(1)
    {
    x = getClk();
    printf("current time is %d\n", x);
    sleep(1);
    }
    destroyClk(true);
}


void ReadFile()
{
    int id;
    int arrivalTime;
    int runningTime;
    int priority;
    FILE *process = fopen("process.txt", "r");
    if (process == NULL)
    {
        printf("Error! File cannot be opened.");
        exit(1);
    }
    while (1)
    {
        char ignoredCharacter[1000];
        fscanf(process, "%s", ignoredCharacter);
        {
            if (*ignoredCharacter == '#')
            {
                fgets(ignoredCharacter, sizeof(ignoredCharacter), process);
                continue;
            }
            else
            {
                id = atoi(ignoredCharacter);
                fscanf(process, "%d %d %d", &arrivalTime, &runningTime, &priority);
                if (feof(process))
                    break;
                setPCB(&processToBeSent, id, arrivalTime, runningTime, priority);
                //printf("id %d, Arr time %d, Running time %d, Priority %d \n", processToBeSent.id, processToBeSent.ArrTime, processToBeSent.RunTime, processToBeSent.Priority);
                AddAccordingToArrivalTime(&que,processToBeSent);
            }
        }
    }
    fclose(process);
}

void IPC()
{
    int upQId = msgget(1234, 0666 | IPC_CREAT);

    if (upQId == -1){
        perror("error in creat");
        exit(-1);
    }
    struct msgBuff processInfo;
    processInfo.mtype = getpid()%10000;
    CopyPCB(&processInfo.process, processToBeSent);
    int val = msgsnd(upQId, &processInfo, sizeof(processInfo.process), IPC_NOWAIT);
    if (val == -1)
        printf("Error in send");
    printf("The send process if is %d\n",processInfo.process.id);
}
void clearResources(int signum)
{
    //TODO Clears all resources in case of interruption
}

void getAlgorithm()
{
    printf("Choose the prefered Algorithm....\n");
    printf("1. HPF \n2. SRTN \n3. RR\n");
    scanf("%d", &Algo);

    while (!(Algo==1||Algo==2||Algo==3))
    {
        printf("Choose A valid Number....\n");
        scanf("%d", &Algo);
        sleep(3);
    }
    if (Algo==3)
    {
        printf("Enter the quantum time....\n");
        scanf("%d", &time_quantum);
    }
    
    //char* Algo_String; 
    //char* time_quantum_String; 
   // sprintf(Algo_String, "%d", Algo);
   // sprintf(time_quantum_String, "%d", time_quantum);

}

void Start_Clk_Scheduler()
{
 int pid;
 for (int i=0;i<2;i++)
 {
     pid= fork();
     if (pid==0)
     {
        if (i==0)
        {
            printf("CLK forking...\n");
            execv("./clk.out",NULL);
            //sleep(10);
        }
        else
        {
            printf("scheduler forking...\n");
            char SendAlgo =Algo + '0';
            char * cSendAlgo = &SendAlgo;
            char SendTime_quantum =time_quantum + '0';
            char * cSendTime_quantum = &SendTime_quantum;
            char* scheduler_arg_list[]={"./scheduler.out",cSendAlgo,cSendTime_quantum,0};
            execve(scheduler_arg_list[0],scheduler_arg_list,NULL); // all the processes should be sent by execve
        }
     }
 }
 
}

// notes
// we should have IO class that is resposnsible for all the IO processes


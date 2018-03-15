#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "MyLib.h"
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
//gcc -o main.exe main.c MyLib.c
FILE* resultFile;

void randomTab(struct Blocks table){
    int i,j;
    for(i=0;i<table.tableSize;i++)
        for(j=0;j<table.blockSize;j++){
            table.table[i][j] = rand() % 100 + 30;
        }
}

struct RandT randomString(struct Blocks block,struct RandT r){
    int i;
    char result[block.blockSize];
    for(i=0;i<block.blockSize;i++){
        result[i] = rand() % 100 + 18;
    }
    r.t_rand = result;
    return r;
}

void throwError(){
    printf("Error\n");
    printf("Program arugments: tableSize blockSize s|d [  [d|D|s][liczba]  ]\n");
    exit(0);
}

double absx(double x){
    if(x > 0) return x;
    return -x;
}

double difference(clock_t t1,clock_t t2){
    return ((double)(t2 - t1) / sysconf(_SC_CLK_TCK));
}

void writeResult(clock_t start,clock_t end,struct tms* t_start,struct tms* t_end){
    printf("REAL_TIME: %fl\n", difference(start,end));
    printf("USER_TIME: %fl\n", difference(t_start->tms_utime,t_end->tms_utime));
    printf("SYSTEM_TIME: %fl\n", difference(t_start->tms_stime,t_end->tms_stime));

    fprintf(resultFile,"REAL_TIME: %fl\n", difference(start,end));
    fprintf(resultFile,"USER_TIME: %fl\n", difference(t_start->tms_utime,t_end->tms_utime));
    fprintf(resultFile,"SYSTEM_TIME: %fl\n", difference(t_start->tms_stime,t_end->tms_stime));
}

int main(int argc,char* argv[])
{
    int i;
    int size = argc + 1;  //zmienic zeby sie nie psulo jak bedzie duzo polecen
    clock_t time[size];
    struct tms *tms[size];
    for (i = 0; i < size; i++){
        tms[i] = calloc(1, sizeof(struct tms *));
        time[i] = 0;
    }

    int isDynamic = 0;
    resultFile = fopen("./raport2a.txt", "a");  //"w"

    //srand(time(NULL));
    struct Blocks blocks;
    if(argc < 3 + 1) throwError();
    int tableSize = atoi(argv[1]);
    int blockSize = atoi(argv[2]);
    if(tableSize == 0 || blockSize == 0) throwError();

    int current_time = 0;
    if(strstr(argv[3],"d") != NULL){
        time[current_time] = times(tms[current_time]);
        current_time += 1;
        blocks = createDynamicBlock(tableSize,blockSize);
        printf("#TABLE SIZE: %d  BLOCK SIZE: %d ALLOCATION DYNAMIC\n",tableSize,blockSize);
        fprintf(resultFile,"#TABLE SIZE: %d  BLOCK SIZE: %d ALLOCATION DYNAMIC\n",tableSize,blockSize);
        isDynamic = 1;
    }
    else{
        if(strstr(argv[3],"s") == NULL) throwError();
        time[current_time] = times(tms[current_time]);
        current_time += 1;
        blocks = createStaticBlock(tableSize,blockSize);
        printf("#TABLE SIZE: %d  BLOCK SIZE: %d ALLOCATION STATIC\n",tableSize,blockSize);
        fprintf(resultFile,"#TABLE SIZE: %d  BLOCK SIZE: %d ALLOCATION STATIC\n",tableSize,blockSize);
    }
    randomTab(blocks);
    time[current_time] = times(tms[current_time]);
    current_time += 1;
    writeResult(time[0],time[1],tms[0],tms[1]);

    int table,action;
    char*tablex;
    for(action=4;action<argc;action++){
        tablex = (char*) malloc(strlen(argv[action])-1);
        strncpy(tablex,argv[action]+1,strlen(argv[action])-1);
        table = atoi(tablex);
        struct RandT r;
        r = randomString(blocks,r);
        time[current_time] = times(tms[current_time]);
        current_time += 1;
        if(strstr(argv[action],"s") != NULL){
            findCloseBlock(blocks,table);
            printf("#SEARCHING %i ELEMENTS\n",table);
            fprintf(resultFile,"#SEARCHING %i ELEMENTS\n",table);
        }else if(strstr(argv[action],"d") != NULL){
            for(i=0;i<table;i++){
                if(isDynamic == 1)
                    deleteBlock(blocks,i);
                else
                    deleteBlockStatic(blocks,i);
            }
            for(i=0;i<table;i++)
                    addToBlock(blocks,i,r.t_rand,blocks.blockSize);
            printf("#REMOVING AND ADDING %i TIMES\n",table);
            fprintf(resultFile,"#REMOVING AND ADDING %i TIMES\n",table);
        }else if(strstr(argv[action],"D") != NULL){
            if(isDynamic == 1){
                for(i=0;i<table;i++){
                    deleteBlock(blocks,i);
                    addToBlock(blocks,i,r.t_rand,blocks.blockSize);
                }
            }else{
                for(i=0;i<table;i++){
                    deleteBlockStatic(blocks,i);
                    addToBlock(blocks,i,r.t_rand,blocks.blockSize);
                }
            }
            printf("#REMOVING %i TIMES AND ADDING %i TIMES\n",table,table);
            fprintf(resultFile,"#REMOVING %i TIMES AND ADDING %i TIMES\n",table,table);
        }

        time[current_time] = times(tms[current_time]);
        current_time += 1;
        writeResult(time[current_time-2],time[current_time-1],tms[current_time-2],tms[current_time-1]);
    }

    printf("\n\n\n");
    fprintf(resultFile,"\n");
    //printTable(blocks);
    deleteTable(blocks);
    fclose(resultFile);
    return 0;
}

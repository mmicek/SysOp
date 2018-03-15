#include "MyLib.h"
#include <stdio.h>
#include <stdlib.h>
#include<stdlib.h>

struct Blocks createDynamicBlock(int sizeTab,int sizeBl){
    char ** block = calloc(sizeTab,sizeof(char*));
    int i;
    for(i= 0;i<sizeTab;i++){
        block[i] = calloc(sizeBl,sizeof(char));
    }
    struct Blocks result;
    result.tableSize = sizeTab;
    result.blockSize = sizeBl;
    result.table = block;
    return result;
}

char table[100000000];
struct Blocks createStaticBlock(int sizeTab,int sizeBl){
    struct Blocks result;
    result.tableSize = sizeTab;
    int i;
    result.blockSize = sizeBl;
    result.table = calloc(sizeTab,sizeof(char*));
    for(i=0;i<sizeTab;i++){
        result.table[i] = &table[i*sizeBl];
    }
    return result;
}

void deleteBlockStatic(struct Blocks table,int index){
    if(index >= table.tableSize) return;
    int i;
    for(i=0;i<table.blockSize;i++)
        table.table[index][i] = 0;
}

void deleteTable(struct Blocks table){
    free(table.table);
}

int addToBlock(struct Blocks table,int index,char * text,int textSize){
    if(index >= table.tableSize) return 0;
    if(table.table[index] == NULL)  table.table[index] = calloc(table.blockSize,sizeof(char));
    int i;
    for(i=0;i<table.blockSize;i++){
        if(i == textSize) break;
        table.table[index][i] = text[i];
    }
    return 1;
}

void printTable(struct Blocks table){
    printf("\n");
    int i,j;
    for(i=0;i<table.tableSize;i++){
        for(j=0;j<table.blockSize;j++){
            printf("%c",(char) table.table[i][j]);
            printf("  ");
        }
        printf("\n");
    }
}

void deleteBlock(struct Blocks table,int index){
    if(index >= table.tableSize) return;
    free(table.table[index]);
    table.table[index] = NULL;
}

int getSum(char*table,int size){
    int result = 0;
    int i;
    for(i=0;i<size;i++){
        result += table[i];
    }
    return result;
}

void printBlock(char* block,int size){
    printf("Najblisze: \n");
    int i;
    for(i=0;i<size;i++){
        printf("%d",block[i]);
        printf("  ");
    }
}

int abs(int x){
    if(x > 0) return x;
    return -x;
}

char* findCloseBlock(struct Blocks table,int number){
    int closestNumber = -9000;
    int closestIndex = -1;
    int i;
    for(i = 0;i<table.tableSize;i++){
        if(table.table[i] == NULL)
            continue;
        if(abs(number - getSum(table.table[i],table.blockSize)) < abs(number - closestNumber)){
            closestIndex = i;
            closestNumber = getSum(table.table[i],table.blockSize);
        }
    }
    if(closestIndex != -1)
        return table.table[closestIndex];
    return NULL;
}

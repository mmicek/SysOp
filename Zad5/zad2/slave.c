#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

//SLAVE

void change(char toWrite[],char from,char to){
    int i=0;
    for(;i<100;i++){
        if(toWrite[i] == from)
            toWrite[i] = to;
    }
}

void clear(char table[]){
    int i=0;
    for(;i<100;i++){
        table[i] = 0;
    }
}

int main(int argv,char* argc[])
{
    srand(time(NULL));
    const int N = atoi(argc[2]);
    char line[100];
    const char* pathName = argc[1];
    int file = open(pathName,O_RDWR);
    printf("%i\n",getpid());

    char toWrite[100];
    FILE* dateInput;

    int i=0;
    while(i<N){
        char pid[100];
        sprintf(pid,"%d",getpid());
        dateInput = popen("date","r");
        fgets(toWrite,100,dateInput);
        pclose(dateInput);
        strcat(pid,"  ");
        strcat(pid,toWrite);
        change(pid,' ','_');
        write(file,pid,100);
        sleep(rand()%5 + 1);
        i++;
    }
    //scanf("%s",toWrite);
    //write(file,toWrite,100);

    return 0;
}

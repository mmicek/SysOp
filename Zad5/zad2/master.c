#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

//MASTER

void change(char toWrite[],char from,char to){
    int i=0;
    for(;i<100;i++){
        if(toWrite[i] == from)
            toWrite[i] = to;
    }
}

int main(int argv,char* argc[])
{
    
    char line[100];
    const char* pathName = argc[1];
    mkfifo(pathName,0666);
    int file = open(pathName,O_RDWR);
    printf("%s\n",pathName);

    while(read(file,line,100) > 0){
	change(line,'_',' ');
        printf("%s\n",line);
    }

    return 0;
}

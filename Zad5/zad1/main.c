#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int fd[2];
int fd2[2];
int fd3[2];
int first;
int last;
void copyTab(char* tab,char line[],int i,int j){
    int x = i;
    int y = 0;
    while(x<j){
        tab[y] = line[x];
        x++; y++;
    }
}
int licz = 0;
char** slice(char line[],int max_n,char c){
    int i=0;
    char** result;
    licz = 0;
    while(i<max_n){
        while(i<max_n && line[i] == c)
            i++;
        while(i<max_n && line[i] != c){
            if(line[i] == '\n') line[i] = c;
            i++;
        }
        licz++;
        if(line[i] == '\n') line[i] = c;
        i++;
    }
    result = calloc(licz+1,sizeof(char*));
    i=0; int l = 0;
    while(i<max_n){
        int last;
        while(i<max_n && line[i] == c)
            i++;
        last = i;
        while(i<max_n && line[i] != c){
            i++;
        }
        result[l] = calloc(i-last,sizeof(char));
        copyTab(result[l],line,last,i);
        l++;
    }

    result[licz] = NULL;
    return result;
}

void runProg(char* prog,char** args){
    execvp(prog,args);
}

void runProgA(char* prog){
    execlp(prog,"",NULL);
}

void pipe2(){
    if(last == 0){
        close(fd2[0]);
        dup2(fd2[1],STDOUT_FILENO);
    }
    if(first == 0)
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
}

void pipe1(){
    if(last == 0){
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
    }
    if(first == 0){
        close(fd2[1]);
        dup2(fd2[0],STDIN_FILENO);
    }
}

int main(int argc,char* argv[])
{
    const int max_n = 50;
    pipe(fd);
    pipe(fd2);
    pipe(fd3);
    first = 1;
    last = 0;
    int pipeNum = 0;

 /*   pid_t pid = fork();
    if (pid == 0) {
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        pipe1();
        execlp("ls","ls","-l",NULL);
    }
    first = 0;
    if(fork() == 0){
        close(fd2[0]);
        dup2(fd2[1],STDOUT_FILENO);
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
       // pipe2();

        execlp("head","head","-n","4", NULL);

    }
    if(fork() == 0){
        //pipe1();
        close(fd3[0]);
       dup2(fd3[1],STDOUT_FILENO);
        close(fd2[1]);
        dup2(fd2[0],STDIN_FILENO);

//execlp("wc","wc","-w",NULL);
       // execlp("sort","sort",NULL);
        execlp("head","head","-n","3",NULL);
    }
    if(fork() == 0){
      //  last = 1;
        close(fd3[1]);
        dup2(fd3[0],STDIN_FILENO);
        //pipe2();
        execlp("head","head","-n","2",NULL);
    }


    return 0;*/


    FILE* file = fopen("./progFile.txt","r");
    char* line;
    char lineTable[max_n][max_n];
    int lineIndex = 0;
    int lineMaxIndex = 0;
    while(fgets(lineTable[lineMaxIndex],max_n,file) != NULL){
        lineMaxIndex ++;
    }
    while(1){
        if(lineIndex == lineMaxIndex) break;
        if(lineIndex == lineMaxIndex - 2) last = 1;
        line = lineTable[lineIndex];
        licz = 0;
        char** result = slice(line,max_n,' ');
        char* prog = result[0];
        char** args = calloc(licz,sizeof(char*));
        int i=1;
        for(;i<licz+1;i++){
            args[i-1] = result[i];
        }

        if(last == 1){
            if(fork() == 0){
                last = 0;
                if(pipeNum == 0) pipe1();
                else pipe2();
                if(licz != 1) runProg(prog,args);
                else runProgA(prog);
                exit(0);
            }
            else{
                first = 0;
                lineIndex ++;
                line = lineTable[lineIndex];
                licz = 0;
                result = slice(line,max_n,' ');
                prog = result[0];
                args = calloc(licz,sizeof(char*));
                i=1;
                for(;i<licz+1;i++){
                    args[i-1] = result[i];
                }
                pipeNum = (pipeNum + 1) % 2;
                last = 1;
                if(pipeNum == 0) pipe1();
                else pipe2();
                if(licz != 1) runProg(prog,args);
                else runProgA(prog);
            }
        }else{
            if(fork() == 0){
                if(pipeNum == 0) pipe1();
                else pipe2();
                if(licz != 1) runProg(prog,args);
                else runProgA(prog);
                exit(0);
            }
        }

        while(wait(NULL) > 0);
        pipeNum = (pipeNum + 1) % 2;
        lineIndex ++;
        free(result);
        first = 0;
        printf("%i\n",lineIndex);
    }
    fclose(file);
    return 0;
}

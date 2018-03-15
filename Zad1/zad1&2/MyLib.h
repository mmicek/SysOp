#ifndef MyLib_h
#define MyLib_h 

struct Blocks{
    int tableSize; //Rozmiar calej tablicy
    int blockSize;
    char ** table;
};
struct RandT{
    char* t_rand;
};

struct Blocks createDynamicBlock(int sizeTab,int sizeBl);
struct Blocks createStaticBlock(int sizeTab,int sizeBl);
void deleteTable(struct Blocks table);
void deleteBlock(struct Blocks table,int index);
int addToBlock(struct Blocks table,int index,char * text,int textSize);
void printTable(struct Blocks table);
char* findCloseBlock(struct Blocks table,int number);
void printBlock(char* block,int size);
void deleteBlockStatic(struct Blocks table,int index);

#endif

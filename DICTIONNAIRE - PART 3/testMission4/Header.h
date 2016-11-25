//
//  Header.h
//  testMission4
//
//  Created by fofo fofodev on 21/11/2016.
//  Copyright © 2016 PROJECT SEMAINE C. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include <stdio.h>
#include <stdlib.h>

struct LinkedList{
    char* value;
    struct LinkedList* next;
};
typedef struct LinkedList LinkedList;



int fileLength(char* file);
void mallocArray(char** array, int size);
void freeArray(char**, int size);
void mainMenu();
char** fillArray(char*,int);
void printArray(char**, int);
char** getMissingWords(char**, int, char**, int);
char** joinArrays(char**, int, char**, int);
int howManyOccurances(char**, int,char*);

LinkedList* newElement(char* v);
void printLinkedList(LinkedList* ll);
LinkedList* fillList(char* filename, LinkedList*);



#endif /* Header_h */

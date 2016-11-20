//
//  gestrech.h
//  DICTIONNAIRE - PART 2
//
//  Created by fofo fofodev on 13/11/2016.
//  Copyright © 2016 PROJECT SEMAINE C. All rights reserved.
//

#ifndef gestrech_h
#define gestrech_h

struct LinkedList{
    char* value;
    struct LinkedList* next;
    
};

typedef struct LinkedList LinkedList;

void menu(LinkedList*);
void menu2(char*,LinkedList*);
void createDictionary(LinkedList*);
void searchWord(char*, LinkedList*);
void displayDictionary(char*);
void dictionaryList(LinkedList*);
LinkedList* newElement(char*);
void printLinkedList(LinkedList*);
void chooseDictionary(LinkedList*);
void addWords(char*, LinkedList*);
int checkName(char*);
void deleteDictionary(char*, LinkedList*);
void deleteWord(char*);

char* getThreshold();
void init(char*, LinkedList*);
int getSign(char*);
int strToThreshold(char*, int);
void displayWords(int,int,char*,LinkedList*);
char* getTheWordToSearch(char*,LinkedList*);


#endif /* gestrech_h */

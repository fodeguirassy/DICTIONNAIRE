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

char* getThreshold(char*, LinkedList*);
void init(char*, LinkedList*);
void displayWords(int,char*,LinkedList*);
char* getTheWordToSearch(char*,LinkedList*);
int my_strcmp(char*, char*,int);
void capital(char *);

int isMissing(char*,char*);
int getNumberOfMissingElements(char**, char*, char*);
char** fillMissingWords(int,char*,char*);
void displayClosers(char*,char**,int);
void mainMenu();


#endif /* gestrech_h */

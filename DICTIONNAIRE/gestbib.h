//
//  functions.h
//  DICTIONNAIRE
//
//  Created by Bérangère La Touche on 16/10/2016.
//  Copyright © 2016 PROJECT SEMAINE C. All rights reserved.
//

#ifndef gestbib_h
#define gestbib_h

#include <stdio.h>

struct LinkedList{
    char* value;
    struct LinkedList* next;
    
};

typedef struct LinkedList LinkedList;

void menu(LinkedList* dictio);
void menu2(char*,LinkedList*);
void createDictionary(LinkedList*);
//void chooseDictionary(LinkedList*);
//void eraseExistingFile(LinkedList*);
//void createNewDictionary(FILE*, char*, char*,LinkedList*);
//void addWordsToDictionary(FILE*, char*, char*,LinkedList*);
void searchWord(char*,LinkedList*);
//void displayDictionary(FILE*, char*, char*,LinkedList*);
//void deleteWord(FILE*, char*, char*,LinkedList*);
//void deleteDictionary(FILE*, char*, char*,LinkedList*);
void dictionaryList();
LinkedList* newElement(char* v);
void printLinkedList(LinkedList* ll);
void chooseDictionary(LinkedList* dictionary);
void addWords(char*, LinkedList*);


#endif /* functions_h */

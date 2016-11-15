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


#endif /* functions_h */

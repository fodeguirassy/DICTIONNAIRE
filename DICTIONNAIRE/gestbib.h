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

void menu();
void menu2(FILE*, char*, char*);
void createDictionary();
void chooseDictionary();
void eraseExistingFile();
void createNewDictionary(FILE*, char*, char*);
void addWordsToDictionary(FILE*, char*, char*);
void searchWord(char*);
void displayDictionary(FILE*, char*, char*);
void deleteWord(FILE*, char*, char*);
void deleteDictionary(FILE*, char*, char*);

#endif /* functions_h */

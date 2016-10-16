//
//  functions.h
//  DICTIONNAIRE
//
//  Created by Bérangère La Touche on 16/10/2016.
//  Copyright © 2016 PROJECT SEMAINE C. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include <stdio.h>

/* Prototypes of functions */
int addWord(char* filename);
void findWord(char* filename);
int linesNumber(FILE* file);
char* readFromStdin(char *message);

#endif /* functions_h */

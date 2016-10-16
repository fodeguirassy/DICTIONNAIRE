//
//  main.c
//  DICTIONNAIRE
//
//  Created by fofo fofodev on 14/10/2016.
//  Copyright © 2016 PROJECT SEMAINE C. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

struct Entry{
    char word[100];
    char description[600];
};

typedef struct Entry Entry;

int main(int argc, const char * argv[]) {
    
    char* file = "source.txt" ;
    
    //int result = addWord(file);
    
    findWord(file);
    //printf("%d\n",result);
    
    
    return 0;
}

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
#include "gestbib.h"


int main(int argc, const char * argv[]) {
    
    char* filename = NULL;
    
    LinkedList* dictionarys = newElement(filename);
    
    //LinkedList* dictionarys;
    menu(dictionarys);
    
    
    
    return 0;
}


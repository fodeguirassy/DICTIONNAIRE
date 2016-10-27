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
<<<<<<< HEAD
        
    char* filename = "source.txt";
    char* dictionary2 = "source4.txt";
    
    LinkedList* dictionarys = newElement(filename);
    dictionarys->next = newElement(dictionary2);
    
    menu(dictionarys);
    
    //createDictionary(dictionarys);
    
    //searchWord(filename);
    
=======

    //menu();

    char* filename = "source.txt";

    searchWord(filename);
    printf("Yo");

>>>>>>> origin/master
    return 0;
}


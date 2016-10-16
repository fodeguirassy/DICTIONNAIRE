//
//  functions.c
//  DICTIONNAIRE
//
//  Created by Bérangère La Touche on 16/10/2016.
//  Copyright © 2016 PROJECT SEMAINE C. All rights reserved.
//

#include "functions.h"

/* Functions */

int addWord(char* filename, char* word){
    int result = 0;
    
    FILE* file = fopen(filename,"a+");
    
    if(file){
        result = 1;
        printf("%d",result);
    }
        
    fclose(file);
    
    return result;
}

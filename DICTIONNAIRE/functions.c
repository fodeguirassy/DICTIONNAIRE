//
//  functions.c
//  DICTIONNAIRE
//
//  Created by Bérangère La Touche on 16/10/2016.
//  Copyright © 2016 PROJECT SEMAINE C. All rights reserved.
//

#include "functions.h"

/* Functions */

int addWord(char* filename){
    int result = 0;
    
    FILE* file = fopen(filename,"w+");
    
    char* word = malloc(sizeof(char) * 56);
    
    printf("Saisissez un mot");
    scanf("%s",word);

    
    if(file){
        //fscanf(file,"%s",word);
        fputs(word,file);
        result = 1;
        
    }
        
    fclose(file);
    
    return result;
}

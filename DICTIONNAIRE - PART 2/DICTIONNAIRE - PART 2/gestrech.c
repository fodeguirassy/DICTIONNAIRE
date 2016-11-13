//
//  gestrech.c
//  DICTIONNAIRE - PART 2
//
//  Created by fofo fofodev on 13/11/2016.
//  Copyright © 2016 PROJECT SEMAINE C. All rights reserved.
//

#include "gestrech.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// launch the application
void init(){
    
    printf("--------------\nTHE DICTIONARY PART 2\n--------------\n\n");
    
    
    char* thresholdStr = getThreshold();
    
    int sign = getSign(thresholdStr);
    
    int thresholdNumber = strToThreshold(thresholdStr, sign);
    
    if(thresholdNumber){
        displayWords(thresholdStr, sign);
    }
    else{
        printf("Wrong entry \t try again!\n");
    }
    
}

// returns the threshold entered by user as
char* getThreshold(){
    
    char* threshold = malloc(sizeof(char)*255);
    printf("Enter the treshold you'd like to apply to your research\n");
    do{
        scanf("%s",threshold);
    
    } while(!threshold);
    
    return threshold;
    
}

// checks and returns weither the value is greater or less than 0
int getSign(char* threshold){
    int result = 0;
    
    if(threshold[0] != 45){
        result = 1;
    }
    return result;
}

//convert the string threshold to an int

int strToThreshold(char* threshold, int sign){
    int number;
    
    char* stringN = malloc(sizeof(char)*255);
    
    if(!sign){
        int j;
        for(int i = 1, j = 0; i < strlen(threshold);i++, j++){
            stringN[j] = threshold[i];
        }
        number = (int)strtol(stringN, NULL, 10);
    }
    else{
        number = (int)strtol(threshold, NULL, 10);
    }
    free(stringN);
    
    return number;
    
}

// open dictionary and display words that fit given threshold
void displayWords(int threshold,int sign){
    
    char* filename = "source.txt";
    
    FILE* dictionary = fopen(filename,"r+");
    if(!dictionary){
        printf("ERROR WHILE OPENING DICTIONARY");
    }
    else{
        printf("ENTER THE WORD YOU WOULD LIKE TO WORK WITH\n");
        char* wordToFind = malloc(sizeof(char)*255);
        scanf("%s",wordToFind);
        
        char* wordFromFile = malloc(sizeof(char)*255);
        
        while (fgets(wordFromFile, 255, dictionary)) {
            
            wordFromFile[strcspn(wordFromFile, "\n")] = '\0';
            if(!sign){
                if(strcmp(wordToFind, wordFromFile) >= (threshold * (-1)) && strcmp(wordToFind, wordFromFile) <= 0){
                    printf("%s\n",wordFromFile);
                }
            }
            else{
                if(strcmp(wordToFind, wordFromFile) >= 0 && strcmp(wordToFind, wordFromFile) <= threshold){
                    printf("%s\n",wordFromFile);
                }
            }
            
        }

    }
    fclose(dictionary);
}

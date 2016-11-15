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
    
    int checked = 0;
    
    char* thresholdStr = getThreshold();
    
    int sign = getSign(thresholdStr);
    
    int thresholdNumber = strToThreshold(thresholdStr, sign);
    
    if(thresholdNumber){
        displayWords(thresholdNumber, sign);
        checked = 1;
    }
    else{
        char* retry = malloc(sizeof(char));
        printf("Wrong entry! Would you like to try again? Enter y or n\n");
        do{
            scanf("%s",retry);
            switch (retry[0]) {
                case 121:
                    init();
                    break;
                case 110:
                    exit(0);
                default:
                    printf("Wrong entry! Enter y or n\n");
                    break;
            }
        }while(!checked);
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
        printf("Error while opening dictionary\n");
    }
    else{
        
        int displayed = 0;
        
        printf("Enter the word you would like to work with\n");
        char* wordToFind = malloc(sizeof(char)*255);
        scanf("%s",wordToFind);
        
        char* wordFromFile = malloc(sizeof(char)*255);
        
        while (fgets(wordFromFile, 255, dictionary)) {
            
            wordFromFile[strcspn(wordFromFile, "\n")] = '\0';
            if(!sign){
                if(strcmp(wordToFind, wordFromFile) >= (threshold * (-1)) && strcmp(wordToFind, wordFromFile) <= 0){
                    printf("%s\n",wordFromFile);
                    displayed = 1;
                }
            }
            else{
                if(strcmp(wordToFind, wordFromFile) >= 0 && strcmp(wordToFind, wordFromFile) <= threshold){
                    printf("%s\n",wordFromFile);
                    displayed = 1;
                }
            }
        }
        
        if(!displayed){
            char* choice = malloc(sizeof(char) *255);
            
            printf("The word you've entered isn't close to any other in this dictionary\n would you like to try with an other word? Enter y or n\n");
            do{
                scanf("%s", choice);
                
                switch (choice[0]){
                    case 121:
                        exit(0);
                        break;
                     case 110 :
                        displayWords(threshold, sign);
                        break;
                    default:
                        printf("Enter y or n\n");
                        break;
                }
                
            }while(choice[0] != 121 && choice[0] != 110);
            
        }

    }
    fclose(dictionary);
}

int getTheWordToSearch(char* word){
    
    printf("Enter the world you would like to work with\n");
    scanf("%s",word);
    
    int checked = 1,i;
    
    for(i = 0; i < strlen(word); i++){
        if(word[i] < 65 ||(word[i] > 90 && word[i] < 97) || word[i] > 122){
            checked = 0;
        }
    }
    
    if(!checked){
        printf("Please make sure you have entered a coorect word\n");
        printf("\nWould you like to try again? Enter y or n\n");
        
        char* choice = malloc(sizeof(char)*255);
        
        do{
            scanf("%s",choice);
            switch (choice[0]) {
                case 121:
                    getTheWordToSearch(word);
                    break;
                case 110:
                    exit(0);
                    break;
                default:
                    printf("Enter y or n\n");
                    break;
            }
            
        }while(choice[0] != 121 && choice[0] != 110);
        
    }
    
    return checked;
}

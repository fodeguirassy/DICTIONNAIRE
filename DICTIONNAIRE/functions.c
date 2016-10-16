//
//  functions.c
//  DICTIONNAIRE
//
//  Created by Bérangère La Touche on 16/10/2016.
//  Copyright © 2016 PROJECT SEMAINE C. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

/* Functions */

int addWord(char* filename){
    int result = 0;
    
    FILE* file = fopen(filename,"w+");
    
    char* word = malloc(sizeof(char) * 56);
    
    printf("Saisissez un mot");
    scanf("%s",word);
    
    if(file){
        fputs(word,file);
        result = 1;
    }
        
    fclose(file);
    free(word);
    return result;
}
void findWord(char* filename){
    int result = 0;
    
    FILE* file = fopen(filename, "r");
    if(file){
        
        int i = 0;
        char c;
        int j = 0;
        
        while((c = fgetc(file)) != EOF){
            char answer[20];
            if(c == '\n'){
                i++;
            }
            else{
                answer[j]= c;
                j++;
            }
            printf("%s\n",answer);
        }
        
        printf("FILE LENGTH %d\n",i);
        
    
        
    
        
        //char* word;
        //word = readFromStdin("A WORD TO FIND");
        //char* string;
        //char answer[20];
        //string = fgets(answer,20,file);
        //printf("%s",word);
        
        result = 1;
    }
    printf("%d\n",result);
    
}

int linesNumber(FILE* file){
    int i = 0;
    char c;
    
    while((c = fgetc(file)) != EOF){
        if(c == '\n'){
           i++;
        }
    }
    return i;
}

char* readFromStdin(char *message){
    printf("%s", message);
    char* text = malloc(sizeof(char)*1024);
    scanf("\n%[^\n]",text);
    return text;
}

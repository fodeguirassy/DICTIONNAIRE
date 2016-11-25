//
//  header.c
//  testMission4
//
//  Created by fofo fofodev on 21/11/2016.
//  Copyright © 2016 PROJECT SEMAINE C. All rights reserved.
//

#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void mainMenu(){
    
    char* textFileName = "source.txt";
    char* dictionary = "dico1.txt";
    
    printf("Text File length : %d\n",fileLength(textFileName));
    printf("Dictio File length : %d\n",fileLength(dictionary));
    int fileSize = fileLength(textFileName);
    int dicoSize = fileLength(dictionary);
    char** arrayText = fillArray(textFileName,fileSize);
    char** arrayDictio = fillArray(dictionary,fileSize);
    printArray(arrayText, dicoSize);
    printf("\n\nWORDS FROM DICTIONARY STARTS HERE\n\n");
    printArray(arrayDictio,fileLength(dictionary));
    printf("\n\nMISSING WORDS FROM DICTIONARY\n\n");
    char** test = getMissingWords(arrayText, fileLength(textFileName), arrayDictio, fileLength(dictionary));
    
}

//newElement() allows to create a new element in a linked list
LinkedList* newElement(char* v){
    LinkedList* ll = malloc(sizeof(LinkedList));
    ll->value = v;
    ll->next = NULL;
    return ll;
}

//printLinkedList() allows to display all the existing dictionary's
void printLinkedList(LinkedList* ll){
    while(ll != NULL){
        printf("%s\n", ll->value);
        ll = ll->next;
    }
}


void mallocArray(char** array, int size){
    
    int i;
    for(i = 0; i < size; i++){
        array[i] = malloc(sizeof(char)*255);
    }
}


void freeArray(char** array, int size){
    
    int i;
    for(i = 0; i < size; i++){
         free(array[i]);
    }
}

int fileLength(char* filename){
    int result = 0;
    FILE* file = fopen(filename,"r");
    
    char* word = malloc(sizeof(char)*255);
    
    if(file != NULL){
        
        while(fgets(word,255,file)){
            result ++;
        }
        
    }
    free(word);
    return result;
}

char** fillArray(char* filename,int size){
    char** array = malloc(size * (sizeof(char)*255));
    
    FILE* file = fopen(filename,"r");
    
    if(file != NULL){
        char* wordFromFile = malloc(sizeof(char)*255);
        int i = 0;
        while (fgets(wordFromFile,255,file)) {
            
            wordFromFile[strcspn(wordFromFile, "\n")] = '\0';

            if(i < size){
                array[i] = malloc(sizeof(char)*255);
                strcpy(array[i],wordFromFile);
            }
            i++;
        }
        //free(wordFromFile);
    }
    fclose(file);
    return array;
    
}
void printArray(char**array, int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%s\n",array[i]);
    }
    
}

int howManyOccurances(char** array, int size,char* string){
    int ocurance = 0;
    int i;
    
    while(i < size){
        if(array[i] == string ){
            ocurance ++;
        }
        i++;
    }
    return ocurance;
}


char** joinArrays(char** arrayText, int textFileSize, char** arrayDictio, int dictioSize){
    char** result = malloc(sizeof(char*)*(textFileSize + dictioSize));
    
    int i;
    int j;
    int k;
    
    for(i = 0; i < textFileSize; i++){
        result[i] = malloc(sizeof(char)*255);
        result[i] = arrayText[i];
    }
    j = textFileSize;
    for(k = 0; k < dictioSize;k++){
        result[j] = malloc(sizeof(char)*255);
        result[j] = arrayDictio[k];
        j++;
    }
    return result;
}

char** getMissingWords(char** arrayText, int textFileSize, char** arrayDictio, int dictioSize){
    int size = textFileSize + dictioSize;
    
    char** result= malloc(sizeof(char*)*size);
    
    result = joinArrays(arrayText, textFileSize, arrayDictio, dictioSize);
    printArray(result,size);
    //printf("\n%d\n",howManyOccurances(result, size,resultBis[0]));
    
    for(int i = 0; i < size; i++){
        if(howManyOccurances(result, size, result[i])){
            printf("HERE'S A MISSING WORD %s\n",result[i]);
        }
    }
    
    return result;
}
LinkedList* fillList(char* filename, LinkedList* ll){
    
    LinkedList* test;
    
    FILE* file = fopen(filename,"r");
    
    if(file){
        char* wordFromFile = malloc(sizeof(char)*255);
        while(fgets(wordFromFile,255,file)) {
            wordFromFile[strcspn(wordFromFile, "\n")] = '\0';
            //ll = malloc(sizeof(LinkedList));
            char* test = malloc(sizeof(char)*255);
            strcpy(test,wordFromFile);
            ll = newElement(test);
            ll = ll->next;
        }
        fclose(file);
    }
    return test;
}


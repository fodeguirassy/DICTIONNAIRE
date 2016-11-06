//
//  functions.c
//  DICTIONNAIRE
//
//  Created by Bérangère La Touche on 16/10/2016.
//  Copyright © 2016 PROJECT SEMAINE C. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/xattr.h>
#include "gestbib.h"


void menu(LinkedList* dictionary) {
    
    
    dictionaryList(dictionary);
    
    char* choice = malloc(sizeof(char));
    
    printf("\n---------------\nLE DICTIONNAIRE\n---------------\nChoose an option (1 to 2)\n\n");
    printf("1. CREATE NEW DICTIONARY\n");
    printf("2. USE A DICTIONARY\n");
    
    do{
        scanf("%s",choice);
        
        switch(*choice) {
            case 49:
                createDictionary(dictionary);
                break;
            case 50:
                printLinkedList(dictionary);
                chooseDictionary(dictionary);
                 menu(dictionary);
                break;
            default:
                printf("INVALID CHOICE ! PLEASE TRY AGAIN\n");
                break;
        }
    }while(*choice != 49 && *choice != 50);
    
    free(choice);
}


LinkedList* newElement(char* v){
    LinkedList* ll = malloc(sizeof(LinkedList));
    ll->value = v;
    ll->next = NULL;
    
    return ll;
}

void printLinkedList(LinkedList* ll){
    
    printf("\nHERE ARE THE DICTIONARYS YOU CAN USE\n");
    
    // boucle itérative tant que ll existe;
    while(ll != NULL){
        if(ll->value != NULL){
            if(checkName(ll->value)){
                printf("%s\n", ll->value);
            }
        }
        ll = ll->next;
        // ll courant devient ll d'après
        //L'équivalent de l'incrémentation d'une variable
    }

}

int checkName(char* astring){
    
    char dot = '.';
    char* extension = ".txt";
    
    char* ret = strchr(astring, dot);
    
    if(ret != NULL && !strcmp(ret, extension)){
        return 1;
    }
    else
        return 0;
}

void dictionaryList(LinkedList* dictionarys) {
    
    DIR* directory = opendir("/Users/fofofofodev/Desktop/ESGI 3A/SEMAINE C/DICTIONNAIRE/DICTIONARYS");
    
    if(directory != NULL) {
        
        struct dirent * content;
                
        while ((content = readdir(directory)) != NULL)
        {
                dictionarys->next = newElement(content->d_name);
                dictionarys = dictionarys->next;
        }
        closedir(directory);
    }
    else
        printf("FAILED TO OPEN DIRECTORY");
}

void menu3(char* dictionaryName,LinkedList* dictionarys){
    
    printf("CHOOSE AN ACTION TO EXECUTE WITH YOUR NEW DICTIONARY - from 1 to 4\n");
    printf("1 - ADD A NEW WORD TO THE NEW DICTIONARY\n");
    printf("2 - SEARCH FOR WORDS IN THE NEW DICTIONARY\n");
    printf("3 - DISPLAY WORDS IN THE NEW DICTIONARY\n");
    printf("4 - GO BACK TO THE MAIN MENU\n");
    
    char *choice = malloc(sizeof(char));
    do{
        scanf("%s",choice);
    
        switch (*choice) {
            case 49:
                addWords(dictionaryName);
                menu3(dictionaryName,dictionarys);
                break;
            case 50:
                searchWord(dictionaryName);
                menu3(dictionaryName,dictionarys);
                break;
            case 51:
                displayDictionary(dictionaryName);
                menu3(dictionaryName,dictionarys);
                break;
            case 52:
                menu(dictionarys);
                break;
            default:
                printf("\n\nPLEASE ENTER A VALID CHOICE\n\n");
                break;
        }
    
    }while(*choice != 49 && *choice != 50 && *choice != 51 && *choice != 52);
}

void createDictionary(LinkedList* dictionarys){
    
    char* dictionaryName = malloc(sizeof(char)*255);
    printf("ENTER A NAME FOR YOUR NEW DICTIONARY\n");
    scanf("%s",dictionaryName);
    
    
    if(dictionaryName != NULL){
        char* extension = ".txt";
        strcat(dictionaryName, extension);
        
        FILE* newDictionary = fopen(dictionaryName,"w");
        
        if(newDictionary != NULL){
            
            dictionaryList(dictionarys);
    
            printf("\n\nYOUR NEW DICTIONARY HAS BEEN SUCCESFULLY CREATED\n\n");
            
            fclose(newDictionary);
            
            menu3(dictionaryName, dictionarys);
            
        }
        else
        {
            printf("ERROR WHILE CREATING THE NEW DICTIONARY\n");
        }
    
    }
    else{
        printf("EMPTY NAMES ARE NOT ALLOWED\n");
    }
    free(dictionaryName);
}

void chooseDictionary(LinkedList* dictionary) {
    
    char* name = malloc(sizeof(char)*255);
    
    printf("ENTER THE NAME OF THE DICTIONARY YOU WANT TO WORK ON\n");
    scanf("%s",name);
    
    if(name != NULL){
        while(dictionary != NULL){
            
            if(dictionary->value != NULL){
                if(!strcmp(name,dictionary->value)){
                    menu2(name,dictionary);
                }
            }
            dictionary = dictionary->next;
        }
    }else{
        printf("YOU'VE ENTERED A WRONG DICTIONNARY NAME\n");
        menu(dictionary);
    }
    free(name);
}

void menu2(char* dictionary , LinkedList* dictionaryList) {
    
    int action = 0;
    
    printf("\n--------\n  MENU\n--------\nChoose an option (1 to 6)\n\n");
    printf("1. SEARCH FOR A WORD IN THE DICTIONARY\n");
    printf("2. DISPLAY WORDS IN THE DICTIONARY\n");
    printf("3. ADD A WORD IN THE DICTIONARY\n");
    printf("4. DESTROY THE DICTIONARY\n");
    printf("5. GO BACK TO THE MAIN MENU\n");
    
    do {
        scanf("%d",&action);
        
        switch (action) {
            case 1:
                searchWord(dictionary);
                menu2(dictionary,dictionaryList);
                break;
            case 2:
                displayDictionary(dictionary);
                menu2(dictionary, dictionaryList);
                break;
            case 3:
                addWords(dictionary);
                menu2(dictionary,dictionaryList);
                break;
            case 4:
                //deleteDictionary();
                break;
            case 5:
                menu(dictionaryList);
                break;
            default:
                printf("Saisie incorrecte ! Réessayer\n");
                break;
        }
    }while (action != 1 && action != 2 && action != 3 && action != 4 && action != 5);
    
}

void displayDictionary(char* dictionaryName){
    
    printf("DICTIONARY NAME THAT YOU'RE WORKING ON IS %s\n",dictionaryName);
    
    FILE* dictionary = fopen(dictionaryName,"r");
    
    char* current = malloc(sizeof(char)*255);
    
    if(dictionary){
        
        while(fgets(current, sizeof(current), dictionary)){
            printf("%s",current);
        }
    }
    else{
        printf("THE DICTIONARY IS NOT AVAILABLE\n");
    }
    
    fclose(dictionary);
    free(current);
}


void searchWord(char* name){
    
    char *wordToFind = malloc(sizeof(char)*255);
    char *answer = malloc(sizeof(char)*1026);
    
    int lineCounter = 0;
    int lineNumber = 0;
    int result = 0;
    
    FILE* dictionary = fopen(name,"r+");
    
    if(dictionary != NULL){
        
        printf("\n\nPLEASE ENTER THE WORD YOU WOULD LIKE TO FIND\n\n");
        scanf("%s",wordToFind);
        
        while(fgets(answer, 255, dictionary)){
            lineCounter++;
            answer[strcspn(answer, "\n")] = '\0';
            if(!strcmp(answer, wordToFind)){
                result = 1;
                lineNumber = lineCounter;
            }
        }
        
        if(result){
            printf("\n\n%s HAS BEEN FOUND AT LINE NUMBER %d\n\n",wordToFind,lineNumber);
        }
        else{
            printf("\n\nTHE WORD YOU'VE ENTERED DOESN'T EXIST IN THIS DICTIONARY\n\n");
        }
        
    }
    else
        printf("\n\nERROR WHILE OPENING THE DICTIONARY\n\n");
    
    fclose(dictionary);
    free(answer);
    free(wordToFind);
}


void addWords(char* name){
    
    int numberOfWords;
    
    printf("HOW MANY WORDS WOULD YOU LIKE TO ADD TO THE DICTIONARY\n");
    scanf("%d",&numberOfWords);
    
    int count = 0;
    char* newWord = malloc(sizeof(char)*255);
    FILE* dictionary = fopen(name,"w");
    
    if(dictionary){
        
        while(count < numberOfWords){
            printf("\nPLEASE ENTER THE NEW WORD YOU WOULD LIKE TO ADD TO THE DICTIONARY\n");
            scanf("%s",newWord);
            fputs(newWord,dictionary);
            fputs("\n",dictionary);
            count++;
        }
    }
    else{
        printf("\nERROR WHILE OPENNING THE DICTIONARY \n\n");
    }
    fclose(dictionary);
    free(newWord);
    
}


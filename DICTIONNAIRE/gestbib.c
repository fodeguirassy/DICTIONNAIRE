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
#include <ctype.h>


//menu() Main menu to choose for create a new dictionary or choose an existing dictionary
void menu(LinkedList* dictionary) {
    
    
    dictionaryList(dictionary);
    
    char* choice = malloc(sizeof(char));
    
    printf("\n---------------\nTHE DICTIONARY\n---------------\nChoose an option (1 to 2)\n\n");
    printf("1. Create new dictionary\n");
    printf("2. Use an existing dictionary\n");
    
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
                printf("Invalid choice ! Please try again\n");
                break;
        }
    }while(*choice != 49 && *choice != 50);
    
    free(choice);
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
    
    printf("\nHere are the dictionarys you can use\n");
    
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

//checkName() allows to check if the needed file have ".txt" extension
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


//dictionaList() put all dictionary's of the directory in a linked list
void dictionaryList(LinkedList* dictionarys) {
    
    DIR* directory = opendir("./");
    
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
        printf("Failed to open dictionary");
}


//createDictionary() allows to create a new dictionary
void createDictionary(LinkedList* dictionarys){
    
    char* dictionaryName = malloc(sizeof(char)*255);
    printf("Enter a name for your new dictionary\n");
    scanf("%s",dictionaryName);
    
    strcat(dictionaryName, ".txt");
    
    if(dictionaryName != NULL){
        
        FILE* newDictionary = fopen(dictionaryName,"w");
        
        if(newDictionary != NULL){
            
            dictionaryList(dictionarys);
    
            printf("\n\nYour new dictionary has been succesfully created\n\n");
            
            fclose(newDictionary);
            
            menu2(dictionaryName, dictionarys);
            
        }
        else
        {
            printf("Error while creating the new dictionary\n");
        }
    
    }
    else{
        printf("Empty names are not allowed\n");
    }
    free(dictionaryName);
}


//chooseDictionary() allows to choose an existing dictionary
void chooseDictionary(LinkedList* dictionary) {
    
    char* name = malloc(sizeof(char)*255);
    
    printf("\nEnter the name of the dictionary you want to work on\n");
    scanf("%s",name);
    
    strcat(name, ".txt");
    
    if(name != NULL) {

        while(dictionary != NULL){
            
            if(dictionary->value != NULL){
                if(!strcmp(name,dictionary->value)){
                    menu2(name,dictionary);
                }else {
                    printf("You've entered a wrong dictionary name\n");
                    chooseDictionary(dictionary);
                }
            }
            dictionary = dictionary->next;
        }
    }else {
        
    }
    
    free(name);
}

//menu2() second menu linked to a dictionary (created or choosen)
void menu2(char* dictionary , LinkedList* dictionaryList) {
    
    char* action = malloc(sizeof(char));
    
    printf("\n--------\n  MENU\n--------\nChoose an option (1 to 5)\n\n");
    printf("1. Search for a word in the dictionary\n");
    printf("2. Display words in the dictionary\n");
    printf("3. Add a word in the dictionary\n");
    printf("4. Destroy the dictionary\n");
    printf("5. Go back to the main menu\n");
    
    do {
        scanf("%s",action);
        
        switch (*action) {
            case 49:
                searchWord(dictionary);
                menu2(dictionary,dictionaryList);
                break;
            case 50:
                displayDictionary(dictionary);
                menu2(dictionary, dictionaryList);
                break;
            case 51:
                addWords(dictionary);
                //menu2(dictionary,dictionaryList);
                break;
            case 52:
                deleteDictionary(dictionary,dictionaryList);
                break;
            case 53:
                menu(dictionaryList);
                break;
            default:
                printf("Wrong entry ! Please retry\n");
                break;
        }
    }while(*action != 49 && *action != 50 && *action != 51 && *action != 52 && *action != 53);
    
}

//displayDictionary() allows to display words of a dictionary (created or choosen)
void displayDictionary(char* dictionaryName){
    
    printf("Dictionary name that you're working on is %s\n",dictionaryName);
    
    FILE* dictionary = fopen(dictionaryName,"r");
    
    char* current = malloc(sizeof(char)*255);
    
    if(dictionary){
        
        while(fgets(current, sizeof(current), dictionary)){
            printf("%s",current);
        }
    }
    else{
        printf("The dictionary is not available\n");
    }
    
    fclose(dictionary);
    free(current);
}


//searchWord() allows to search a word in a dictionary (created or choosen)
void searchWord(char* name){
    
    char *wordToFind = malloc(sizeof(char)*255);
    char *answer = malloc(sizeof(char)*1026);
    
    int lineCounter = 0;
    int lineNumber = 0;
    int result = 0;
    
    FILE* dictionary = fopen(name,"r+");
    
    if(dictionary != NULL){
    
        printf("\n\nPlease enter the word you would like to find\n\n");
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
            printf("\n\n%s has been found at line number %d\n\n",wordToFind,lineNumber);
        }
        else{
            printf("\n\nThe word you've entered doesn't exist in this dictionary\n\n");
        }
        
    }
    else
        printf("\n\Error while opening the dictionary\n\n");
    
    fclose(dictionary);
    free(answer);
    free(wordToFind);
}

//deleteWords() allows to delete a word of a dictionary (created or choosen)
void deleteWord(char* name){
    
    char *wordToFind = malloc(sizeof(char)*255);
    char *answer = malloc(sizeof(char)*1026);
    
    int lineCounter = 0;
    int lineNumber = 0;
    int result = 0;
    
    FILE* dictionary = fopen(name,"r+");
    
    if(dictionary != NULL){
        
        printf("\n\nPlease enter the word you would like to find\n\n");
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
            printf("\n\n%s has been found at line number %d\n\n",wordToFind,lineNumber);
        }
        else{
            printf("\n\nThe word you've entered doesn't exist in this dictionary\n\n");
        }
        
    }
    else
    printf("\n\Error while opening the dictionary\n\n");
    
    fclose(dictionary);
    free(answer);
    free(wordToFind);
}

//addWords() allows to add words to a dictionary (created or choosen)
void addWords(char* name){
    
    int numberOfWords;
    int count = 0;
    char* newWord = malloc(sizeof(char)*255);
    
    printf("How many words would you like to add to the dictionary\n");
    scanf("%d",&numberOfWords);
    
    //if(isdigit(numberOfWords)) {
        FILE* dictionary = fopen(name,"a+");
        
        if(dictionary){
            
            printf("\nPlease enter the new word you would like to add to the dictionary\n");
            
            while(count < numberOfWords){
                scanf("%s",newWord);
                fputs(newWord,dictionary);
                fputs("\n",dictionary);
                count++;
            }
            
            printf("\nYour words have been added succesfully\n");
        }
        else{
            printf("\nError while oppening the dictionary \n\n");
        }
        fclose(dictionary);
    //}else {
      //  printf("Wrong entry ! Please retry\n");
        //addWords(name);
    //}
    
    free(newWord);
    
}

//deleteDictionary() allows to delete a dictionary
void deleteDictionary(char* name, LinkedList* dictionaryList) {
    
    char* choice = malloc(sizeof(char));
    
    FILE* dictionary = fopen(name,"w+");
    
    if(dictionary != NULL) {
        
        printf("\nAre you sure you want to delete %s y/n\n",name);
        
        do {
            scanf("%s",choice);
            switch (*choice) {
                case 121:
                remove(name);
                break;
                case 110:
                menu2(name, dictionaryList);
                break;
                default:
                printf("Wrong entry ! Please retry\n");
                break;
            }
        }while(*choice != 121 && *choice != 110);
        
        printf("\nThe dictionary %s has been deleted succesfully\n\n",name);
        
        menu(dictionaryList);
        
        fclose(dictionary);
    }else {
        printf("Error !");
        menu(dictionaryList);
        fclose(dictionary);
    }
}


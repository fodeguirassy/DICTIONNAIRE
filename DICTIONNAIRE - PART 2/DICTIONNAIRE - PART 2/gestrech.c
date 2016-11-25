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
#include <regex.h>
#include <dirent.h>


//menu() Main menu to choose for create a new dictionary or choose an existing dictionary
void menu(LinkedList* dictionary) {
    
    
    dictionaryList(dictionary);
    
    char* choice = malloc(sizeof(char));
    
    printf("-----------------------\nTHE DICTIONARY - PART 2\n-----------------------\nChoose an option (1 to 2)\n\n");
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
    
    while(ll != NULL){
        if(ll->value != NULL){
            if(checkName(ll->value)){
                printf("%s\n", ll->value);
            }
        }
        ll = ll->next;
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
            if(checkName(content->d_name)){
                dictionarys->next = newElement(content->d_name);
                dictionarys = dictionarys->next;
            }
        }
        closedir(directory);
    }else {
        printf("Failed to open dictionary");
    }
}


//createDictionary() allows to create a new dictionary
void createDictionary(LinkedList* dictionarys){
    
    char* dictionaryName = malloc(sizeof(char)*255);
    int create = 0;
    //dictionaryList(dictionarys);
    FILE* newDictionary = NULL;
    
    if(dictionarys->value == NULL) {
        dictionarys = dictionarys->next;
    }
    
    do {
        printf("Enter a name for your new dictionary\n");
        scanf("%s",dictionaryName);
        
        if(strcmp(dictionaryName, "\e") == 0) {
            menu(dictionarys);
        }
        
        strcat(dictionaryName, ".txt");
        
        if(dictionaryName != NULL){
            
            newDictionary = fopen(dictionaryName,"r+");
            
            if(newDictionary == NULL){
                newDictionary = fopen(dictionaryName, "w");
                dictionaryList(dictionarys);
                create = 1;
                printf("\nYour new dictionary has been succesfully created\n\n");
                fclose(newDictionary);
                menu2(dictionaryName, dictionarys);
            }else {
                fclose(newDictionary);
            }
            
        }else{
            printf("Empty names are not allowed\n");
        }
        printf("This dictionary already exist, please retry\n");
    }while(!create);
    
    free(dictionaryName);
}


//chooseDictionary() allows to choose an existing dictionary
void chooseDictionary(LinkedList* dictionary) {
    
    char* name = malloc(sizeof(char)*255);
    char* choice = malloc(sizeof(char));
    
    if(dictionary->value == NULL) {
        dictionary = dictionary->next;
    }
    
    int found = 0;
    do {
        LinkedList* head = dictionary;
        printf("\nEnter the name of the dictionary you want to work on\n");
        scanf("%s",name);
        
        if(strcmp(name,"\e") == 0) {
            menu(dictionary);
        }
        
        strcat(name, ".txt");
        
        while(head != NULL && head->value != NULL){
            if(strcmp(name, head->value) == 0){
                menu2(name,head);
                found = 1;
                break;
            }
            head = head->next;
        }
        
        do {
            printf("This dictionary doesn't exist, would you like to create one ? y/n\n");
            scanf("%s",choice);
            switch (*choice) {
                case 121:
                    createDictionary(dictionary);
                    break;
                    
                case 110:
                    continue;
                    break;
                    
                case 27:
                    menu(dictionary);
                    break;
                    
                default:
                    printf("Wrong entry ! Please retry\n");
                    break;
            }
        }while (*choice != 121 && *choice != 110 && *choice != 27);
        
    }while(!found);
    
    free(name);
}

//menu2() second menu linked to a dictionary (created or choosen)
void menu2(char* dictionary , LinkedList* dictionaryList) {
    
    char* action = malloc(sizeof(char));
    
    printf("\n--------\n  MENU\n--------\nChoose an option (1 to 7)\n\n");
    printf("1. Search for a word in the dictionary\n");
    printf("2. Display words in the dictionary\n");
    printf("3. Add a word in the dictionary\n");
    printf("4. Advanced research with near list of words\n");
    printf("5. Delete word in the dictionary\n");
    printf("6. Destroy the dictionary\n");
    printf("7. Go back to the main menu\n");
    
    do {
        scanf("%s",action);
        
        switch (*action) {
            case 49:
                searchWord(dictionary,dictionaryList);
                menu2(dictionary,dictionaryList);
                break;
            case 50:
                displayDictionary(dictionary);
                menu2(dictionary, dictionaryList);
                break;
            case 51:
                addWords(dictionary, dictionaryList);
                menu2(dictionary,dictionaryList);
                break;
            case 52:
                init(dictionary, dictionaryList);
                menu2(dictionary,dictionaryList);
                break;
            case 53:
                deleteWord(dictionary);
                menu2(dictionary, dictionaryList);
                break;
            case 54:
                deleteDictionary(dictionary,dictionaryList);
                break;
            case 55:
                menu(dictionaryList);
                break;
            default:
                printf("Wrong entry ! Please retry\n");
                break;
        }
    }while(*action != 49 && *action != 50 && *action != 51 && *action != 52 && *action != 53 && *action != 54 && *action != 55);
    
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
void searchWord(char* name, LinkedList* dictionarys){
    
    char *wordToFind = malloc(sizeof(char)*255);
    char *answer = malloc(sizeof(char)*1026);
    
    int lineCounter = 0;
    int lineNumber = 0;
    int count = 0;
    int result = 0;
    int returnScanf = 0;
    
    FILE* dictionary = fopen(name,"r+");
    
    if(dictionary != NULL){
        
        do {
            printf("\nPlease enter the word you would like to find\n");
            getchar();
            returnScanf = scanf("%[\ea-zA-ZÀÁÂÆÇÈÉÊËÌÍÎÏÑÒÓÔŒÙÚÛÜÝŸàáâæçèéêëìíîïñòóôœùúûüýÿ'-]s",wordToFind);
            
            if(strcmp(wordToFind, "\e") == 0) {
                menu2(name, dictionarys);
            }
            
            scanf ("%*[^\n]");
            
            
            if(returnScanf != 0) {
                count = 1;
                while(fgets(answer, 255, dictionary)){
                    lineCounter++;
                    answer[strcspn(answer, "\n")] = '\0';
                    if(!strcmp(answer, wordToFind)){
                        result = 1;
                        lineNumber = lineCounter;
                    }
                }
                
                if(result){
                    printf("\n%s has been found at line number %d\n",wordToFind,lineNumber);
                }
                else{
                    printf("\nThe word you've entered doesn't exist in this dictionary\n");
                }
                
            }else {
                printf("\nYour input can contain letters only ! Please retry\n");
            }
            
        }while(!count);
        
        
    }else {
        
        printf("\n\Error while opening the dictionary\n\n");
        
    }
    
    fclose(dictionary);
    free(answer);
    free(wordToFind);
}

//deleteWords() allows to delete a word of a dictionary (created or choosen)
void deleteWord(char* name){
    
    char *wordToDelete = malloc(sizeof(char)*255);
    char *answer = malloc(sizeof(char)*1026);
    
    int lineCounter = 0;
    int lineNumber = 0;
    int result = 0;
    
    FILE* dictionary = fopen(name,"r+");
    
    if(dictionary != NULL){
        
        printf("\n\nPlease enter the word you would like to delete\n\n");
        scanf("%s",wordToDelete);
        
        while(fgets(answer, 255, dictionary)){
            lineCounter++;
            answer[strcspn(answer, "\n")] = '\0';
            if(!strcmp(answer, wordToDelete)){
                fseek(dictionary, lineCounter, SEEK_CUR);
                //fputc(' ', dictionary);
                fputs(" ", dictionary);
                result = 1;
                lineNumber = lineCounter;
            }
        }
        
        if(result){
            printf("\n%s has been found at line number %d\n",wordToDelete,lineNumber);
        }
        else{
            printf("\nThe word you've entered doesn't exist in this dictionary\n");
        }
    }else {
        printf("\n\Error while opening the dictionary\n\n");
    }
    
    fclose(dictionary);
    free(answer);
    free(wordToDelete);
}

//addWords() allows to add words to a dictionary (created or choosen)
void addWords(char* name, LinkedList* dictionaryList){
    
    char* numberOfWords = malloc(sizeof(char));
    int nb = 0;
    int count = 0;
    int cpt = 0;
    char* newWord = malloc(sizeof(char)*255);
    int returnScanf;
    
    do {
        printf("How many words would you like to add to the dictionary\n");
        getchar();
        returnScanf = scanf("%[\e0-9]s",numberOfWords);
        
        if(strcmp(numberOfWords, "\e") == 0) {
            menu2(name, dictionaryList);
        }
        
        scanf ("%*[^\n]");
        
        if(returnScanf != 0) {
            cpt = 1;
            FILE* dictionary = fopen(name,"a+");
            
            if(dictionary){
                printf("\nPlease enter the new word you would like to add to the dictionary\n");
                
                nb = atoi(numberOfWords);
                while(count < nb){
                    getchar();
                    returnScanf = scanf("%[\ea-zÀÁÂÆÇÈÉÊËÌÍÎÏÑÒÓÔŒÙÚÛÜÝŸàáâæçèéêëìíîïñòóôœùúûüýÿ'-]s",newWord);
                    
                    if(strcmp(newWord, "\e") == 0){
                        addWords(name, dictionaryList);
                    }
                    
                    if(strcmp(newWord, "\e\e") == 0) {
                        menu2(name, dictionaryList);
                    }
                    
                    scanf ("%*[^\n]");
                    if(returnScanf != 0) {
                        fputs(newWord,dictionary);
                        fputs("\n",dictionary);
                        count++;
                    }else {
                        printf("Your input can contain letters only and 2 minimum ! Please retry\n");
                    }
                }
                
                printf("\nYour words have been added succesfully\n");
            }
            else{
                printf("\nError while oppening the dictionary \n\n");
            }
            fclose(dictionary);
        }else {
            printf("Your input can contain numbers only ! Please retry\n");
        }
    }while(!cpt);
    
    free(newWord);
    free(numberOfWords);
    
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
                    
                case 27:
                    menu2(name, dictionaryList);
                    break;
                    
                default:
                    printf("Wrong entry ! Please retry\n");
                    break;
            }
        }while(*choice != 121 && *choice != 110 && *choice != 27);
        
        printf("\nThe dictionary %s has been deleted succesfully\n\n",name);
        
        menu(dictionaryList);
        
        fclose(dictionary);
    }else {
        printf("Error !");
        menu(dictionaryList);
        fclose(dictionary);
    }
}





// launch the application
void init(char* name, LinkedList* dictionarys){
    
    char* retry = malloc(sizeof(char));
    char* thresholdStr = malloc(sizeof(char));
    int checked = 0;
    int threshold = 0;
    
    thresholdStr = getThreshold(name, dictionarys);

    threshold = atoi(thresholdStr);
    
    if(threshold){
        displayWords(threshold, name, dictionarys);
        checked = 1;
    }
    
    while(!checked){
        
        do{
            printf("Wrong entry! Would you like to try again? y/n\n");
            scanf("%s",retry);
            switch (*retry) {
                case 121:
                    init(name,dictionarys);
                    break;
                case 110:
                    menu2(name,dictionarys);
                default:
                    printf("Wrong entry! Please retry\n");
                    break;
            }
        }while(*retry != 121 && *retry != 110);
    }
    
}

// returns the threshold entered by user as
char* getThreshold(char* name, LinkedList* dictionarys){
    
    char* threshold = malloc(sizeof(char)*255);
    int returnScanf = 0;

    do{
        printf("\nEnter the treshold you'd like to apply to your research\n");
        getchar();
        returnScanf = scanf("%[\e0-9]s",threshold);
        
        if(strcmp(threshold, "\e") == 0) {
            menu2(name, dictionarys);
        }
        
        scanf("%*[^\n]");
        
        if(returnScanf == 0) {
            printf("You're input can contains numbers only ! Please retry\n");
        }
    
    } while(returnScanf == 0);
    
    return threshold;
    
}

//convert capital letters in tiny letters
void capital(char *string)
{
    int i = 0;
    
    for (i = 0; string[i] != '\0'; i ++)
    {
        if (string[i] >= 'A' && string[i] <= 'Z')
        {
            string[i] -= 'A' - 'a';
            string[i] = string[i] - 'A' - 'a';
        }
    }
}

//compare strings to find different caracter
int my_strcmp(char* str1, char* str2, int treshold) {
    
    int count = 0;
    int tmp = 0;
    int i;
    char* str = malloc(sizeof(char));
    char* min = malloc(sizeof(char));
    
    capital(str1);
    capital(str2);
    
    if(strlen(str1) < strlen(str2)) {
        str = str2;
    }else {
        str = str1;
    }

    min = str1;
    
    for (i = 0; str[i] != '\0'; i++) {
        if(str1[i] == str2[i]){
            tmp++;
        }
        if(tmp == strlen(min)) {
            if(str1[i+1] != str2[i+1]) {
                count++;
                /*if(str2[i] > 122) {
                    count--;
                }*/
            }
        }
    }
    
    return count;
    
}

// open dictionary and display words that fit given threshold
void displayWords(int threshold, char* name, LinkedList* dictionarys){
    
    FILE* dictionary = fopen(name,"r+");
    char* choice = malloc(sizeof(char) *255);
    char* wordFromFile = malloc(sizeof(char)*255);
    char* wordToFind = malloc(sizeof(char) * 255);
    int displayed = 0;
    
    if(!dictionary){
        printf("Error while opening dictionary\n");
    }
    else{
        
        //executes only if entered word is a real string
        wordToFind = getTheWordToSearch(name,dictionarys);
        
        
        while (fgets(wordFromFile, 255, dictionary)) {
            
            wordFromFile[strcspn(wordFromFile, "\n")] = '\0';

            if(my_strcmp(wordToFind, wordFromFile, threshold) == threshold){
                printf("%s\n",wordFromFile);
                displayed = 1;
            }
        }

        free(wordToFind);
        free(wordFromFile);
        
        
        //launch a second try if word to search wasn't found
        if(!displayed){
            
            printf("The word you've entered isn't close to any other in this dictionary would you like to try with an other word? y/n\n");
            do{
                scanf("%s", choice);
                
                switch (choice[0]){
                    case 121:
                        displayWords(threshold, name, dictionarys);
                        break;
                     case 110 :
                        menu2(name, dictionarys);
                        break;
                    default:
                        printf("Wrong entry ! Please retry\n");
                        break;
                }
                
            }while(choice[0] != 121 && choice[0] != 110);
            
        }

    }
    fclose(dictionary);
}

char* getTheWordToSearch(char* name, LinkedList* dictionarys){
    
    char* word = malloc(sizeof(char)*255);
    char* choice = malloc(sizeof(char)*255);
    int returnScanf = 0;
    
    printf("Enter the word you would like to work with\n");
    getchar();
    returnScanf = scanf("%[\ea-zA-ZÀÁÂÆÇÈÉÊËÌÍÎÏÑÒÓÔŒÙÚÛÜÝŸàáâæçèéêëìíîïñòóôœùúûüýÿ'-]s",word);
    
    if(strcmp(word, "\e") == 0) {
        getTheWordToSearch(name,dictionarys);
    }
    
    if(strcmp(word, "\e\e") == 0) {
        init(name,dictionarys);
    }
    
    scanf("%*[^\n]");
    
    if(returnScanf == 0){
        printf("Please make sure you have entered a correct word\n");
        printf("Would you like to try again? y/n\n");
        
        do{
            scanf("%s",choice);
            switch (*choice) {
                case 121:
                    getTheWordToSearch(name,dictionarys);
                    break;
                case 110:
                    menu2(name, dictionarys);
                    break;
                default:
                    printf("Wrong entry ! Please retry\n");
                    break;
            }
            
        }while(*choice != 121 && *choice != 110);
        
    }
    
    return word;
    
}

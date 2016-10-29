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
    printLinkedList(dictionary);
    
    char* choice = malloc(sizeof(char));
    
    
    
    printf("\n---------------\nLE DICTIONNAIRE\n---------------\nChoose an option (1 to 2)\n\n");
    printf("1. Créer un dictionnaire\n");
    printf("2. Utiliser un dictionnaire existant\n");
    
    do{
        
        
        scanf("%s",choice);
        
        switch(*choice) {
            case 49:
                createDictionary(dictionary);
                menu(dictionary);
                break;
            case 50:
                chooseDictionary(dictionary);
                 menu(dictionary);
                break;
            default:
                printf("Saisie incorrecte ! Réessayer\n");
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
    // boucle itérative tant que ll existe;
    while(ll != NULL){
        printf("%s\n", ll->value);
        ll = ll->next; // ll courant devient ll d'après
        //L'équivalent de l'incrémentation d'un compteur mais pour une linkedlist
    }
    printf("\n");
}



void dictionaryList(LinkedList* dictionarys) {
    
    DIR* directory = opendir("DICTIONARYS");
    
    if(directory != NULL) {
        
        struct dirent * content;
        
        while ((content = readdir(directory)) != NULL)
        {
            dictionarys->next = newElement(content->d_name);
            dictionarys = dictionarys->next;
        }
        
        closedir(directory);
        
    }
}


void createDictionary(LinkedList* dictionaryList){

    printLinkedList(dictionaryList);
    
    
    char* dictionaryName = malloc(sizeof(char)*255);
    printf("ENTER A NAME FOR YOUR NEW DICTIONARY\n");
    scanf("%s",dictionaryName);
    
    if(dictionaryName != NULL){
        
        FILE* newDictionary = fopen(dictionaryName,"w");
        
        if(newDictionary != NULL){
            
            printf("YOUR NEW DICTIONARY HAS BEEN CREATED\n");
            dictionaryList->next = newElement(dictionaryName);
            dictionaryList = dictionaryList->next;
            
            
            printf("HERE IS THE NEW LIST OF YOUR DICTIONARYS\n");
            printLinkedList(dictionaryList);
            
            
            fclose(newDictionary);
        }
        else
        {
            printf("ERROR WHILE CREATING THE NEW DICTIONARY\n");
            
        }
    }
    else{
        printf("PLEASE ENTER A VALID NAME\n");
            }
    
    free(dictionaryName);
}

void chooseDictionary(LinkedList* dictionary) {
    
    char* name = malloc(sizeof(char)*255);
    
    printf("ENTER THE NAME OF THE DICTIONARY YOU WANT TO WORK ON\n");
    scanf("%s",name);
    
    if(name != NULL){
        while(dictionary != NULL){
            if(!strcmp(name,dictionary->value)){
                menu2(name,dictionary);
            }
            
            dictionary = dictionary->next;
        }
        
    }else{
        printf("YOU'VE ENTERED A WRONG DICTIONNARY NAME\n");
        menu(dictionary);
    }
    
    free(name);
    
}

//void createNewDictionary(FILE* dictionary, char* path, char* name, LinkedList* dictionaryList) {
//    
//    printf("\nFélicitations vous avez créer le dictionnaire %s\n",name);
//    
//    menu2(dictionary, name, path,dictionaryList);
//    
//}

void menu2(char* dictionary , LinkedList* dictionaryList) {
    
    int action = 0;
    
    printf("\n--------\n  MENU\n--------\nChoose an option (1 to 6)\n\n");
    printf("1. Rechercher un mot dans le dictionnaire\n");
    printf("2. Afficher le dictionnaire\n");
    printf("3. Ajouter un mot au dictionnaire\n");
    printf("4. Supprimer un mot du dictionnaire\n");
    printf("5. Supprimer le dictionnaire\n");
    printf("6. Revenir au menu principal\n");
    
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
                //deleteWord(dictionary, dictionaryList);
                break;
            case 5:
                //deleteDictionary(dictionary, dictionaryList);
                break;
            case 6:
                menu(dictionaryList);
                break;
            default:
                printf("Saisie incorrecte ! Réessayer\n");
                break;
        }
    }while (action != 1 && action != 2 && action != 3 && action != 4 && action != 5);
    
}

void displayDictionary(char* dictionaryName){
    
    printf("DICTIONARY NAME THAT YOU4RE WORKING ON IS %s\n",dictionaryName);
    
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
    
    FILE* dictionary = fopen(name,"r+");
    
    if(dictionary != NULL){
        
        printf("PLEASE ENTER THE WORD YOU WOULD LIKE TO FIND\n");
        scanf("%s",wordToFind);
        
        while(fgets(answer, 255, dictionary)){
            lineCounter++;
            answer[strcspn(answer, "\n")] = '\0';
            if(!strcmp(answer, wordToFind)){
                printf("%s HAS BEEN FOUND AT LINE NUMBER %d\n",answer,lineCounter);
            }
        }
        
            }
    else
        printf("ERROR WHILE OPENING THE DICTIONARY\n");
    
    fclose(dictionary);
    free(answer);
    free(wordToFind);
}


//void displayDictionary(FILE* dictionary, char* name, char* path, LinkedList* dictionaryList) {
//    
//    char* read_word = malloc(sizeof(char) * 255);
//    
//    dictionary = fopen(path, "r+");
//    
//    if(dictionary != NULL) {
//        printf("\nDictionnaire: %s\n",name);
//        while(fgets(read_word, 255, dictionary)) {
//            printf("%s",read_word);
//        }
//        fclose(dictionary);
//    }else {
//        printf("Erreur !\n");
//        menu(dictionaryList);
//        fclose(dictionary);
//    }
//    
//}

void addWords(char* name){
    
    int numberOfWords;
    
    printf("HOW MANY WORDS WOULD YOU LIKE TO ADD TO THE DICTIONARY\n");
    scanf("%d",&numberOfWords);
    
    int count = 0;
    char* newWord = malloc(sizeof(char)*255);
    FILE* dictionary = fopen(name,"w");
    
    
    if(dictionary){
        
        while(count < numberOfWords){
            printf("PLEASE ENTER THE NEW WORD YOU WOULD LIKE TO ADD TO THE DICTIONARY\n");
            scanf("%s",newWord);
            
            fputs(newWord,dictionary);
            fputs("\n",dictionary);
            
            count++;
        }
    }
    else{
        printf("IT IS NOT ANY DICTIONARY");
    }
    fclose(dictionary);
    free(newWord);
    
}

//void addWordsToDictionary(FILE * dictionary, LinkedList* dictionaryList) {
//    
//    int nb_words, count = 0;
//    char* words = malloc(sizeof(char) * 255);
//    
//    dictionary = fopen(path, "a+");
//    
//    if(dictionary != NULL) {
//        
//        printf("\nVeuillez indiquer le nombre de mots que vous souhaitez ajouter:\n");
//        scanf("%d",&nb_words);
//        
//        printf("\nVeuillez saisir les %d mots que vous souhaitez ajouter:\n",nb_words);
//        
//        while(count < nb_words) {
//            
//            scanf("%s",words);
//            fputs(words,dictionary);
//            fputs("\n", dictionary);
//            count++;
//            
//        }
//        
//        fclose(dictionary);
//    }else {
//        printf("Erreur ! Le fichier n'existe pas ou est endomagé. \n");
//        menu(dictionaryList);
//        fclose(dictionary);
//    }
//    
//    printf("\nFélicitations !\nVous venez d'ajouter des mots au dictionnaire %s\n",name);
//    
//    menu2(dictionary, name, path,dictionaryList);
//    
//}



//void deleteWord(FILE* dictionary, char* name, char* path, LinkedList* dictionaryList) {
//    
//    char* delete_words = malloc(sizeof(char) * 255);
//    //char* stringToDelete = malloc(sizeof(char) * 255);
//    char* string = malloc(sizeof(char) * 255);
//    int nb_words = 0, i = 0;
//    displayDictionary(dictionary, name, path,dictionaryList);
//    
//    dictionary = fopen(path, "r+");
//    
//    if(dictionary != NULL) {
//        printf("\nVeuillez saisir le nombre de mots que vous souhaitez supprimer:\n");
//        scanf("%d",&nb_words);
//        
//        printf("Quel(s) sont les mots que vous souhaitez supprimer ?\n");
//        //int count = 0, k = 0;
//        for(i = 0; i < nb_words; i++) {
//            //int count = 0;
//            //string = 0;
//            printf("Saisir:");
//            scanf("%s",delete_words);
//            while ((fgets(string,22,dictionary) != '\0')) {
//                //while(string != '\0') {
//                if(strcmp(&string[i], &delete_words[i]) != 0) {
//                    printf("%s",&string[i]);
//                    //fputs("\0", dictionary);
//                }else {
//                    printf("pas le meme mot");
//                }
//                    //count++;
//                //}
//                /*while(delete_words[count] == string && delete_words[count] != '\n') {
//                    count++;
//                    fseek(dictionary, -1, SEEK_CUR);
//                    fputc(' ', dictionary);
//                    //stringToDelete[k] = string;
//                    k++;
//                }*/
//           }
//            
//            //printf("mot à supprimer: %s\n",stringToDelete);
//            //fseek(dictionary, 0, SEEK_SET);
//        }
//        /*while(fgets(stringToDelete, 255, dictionary)) {
//            if(stringToDelete == NULL) {
//                printf("chaine vide : %s",stringToDelete);
//            }
//            //fputs("\0", dictionary);
//        }*/
//        //displayDictionary(dictionary, name, path);
//        fclose(dictionary);
//    }else {
//        printf("Erreur !");
//        menu(dictionaryList);
//        fclose(dictionary);
//    }
//    
//}

//void deleteDictionary(FILE* dictionary, char* name, char* path, LinkedList* dictionaryList) {
//    
//    char* choice = malloc(sizeof(char));
//    
//    dictionary = fopen(path,"w+");
//    
//    if(dictionary != NULL) {
//        
//        printf("\nÊtes-vous sûr de vouloir supprimer le dictionnaire %s o/n\n",name);
//        
//        do {
//            scanf("%s",choice);
//            switch (*choice) {
//                case 111:
//                    remove(path);
//                    break;
//                case 110:
//                    menu2(dictionary, name, path,dictionaryList);
//                    break;
//                default:
//                    printf("Saisie incorrect ! Réessayer\n");
//                    break;
//            }
//        }while(*choice != 111 && *choice != 110);
//        
//        printf("\nLe dictionnaire %s a bien été supprimé\n\n",name);
//        
//        menu2(dictionary, name, path,dictionaryList);
//        
//        fclose(dictionary);
//    }else {
//        printf("Erreur !");
//        menu(dictionaryList);
//        fclose(dictionary);
//    }
//}

//    char* choice = malloc(sizeof(char));
//    char* name = malloc(sizeof(char) * 255);
//    FILE * dictionary;
//    char path[255] = "/Users/berangerelatouche/Documents/fichiers_dico/";
//
//    printf("\nVeuillez nommer votre dictionnaire:\n");
//    scanf("%s",name);
//
//    strcat(name, ".txt");
//    strcat(path,name);
//
//    dictionary = fopen(path,"w");
//
//    if(dictionary != NULL) {
//
//        createNewDictionary(dictionary, path, name,dictionaryList);
//        fclose(dictionary);
//
//    }else {
//        printf("\nAttention ce fichier existe déjà !\nSi vous continuez, le contenu de ce fichier sera écrasé. Continuer ? o/n\n");
//        do {
//            scanf("%s",choice);
//
//            switch(*choice) {
//                case 111:
//                    createNewDictionary(dictionary, path, name,dictionaryList);
//                    break;
//                case 110:
//                    createDictionary(dictionaryList);
//                    break;
//                default:
//                    printf("\nSaisie incorrecte ! Réessayer\n");
//                    break;
//            }
//        }while(*choice != 111 && *choice != 110);
//
//        fclose(dictionary);
//    }




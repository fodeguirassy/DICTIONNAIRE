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
    
    char* choice = malloc(sizeof(char));
    
    printf("\n---------------\nLE DICTIONNAIRE\n---------------\nChoose an option (1 to 2)\n\n");
    printf("1. Créer un dictionnaire\n");
    printf("2. Utiliser un dictionnaire existant\n");
    
    do{
        scanf("%s",choice);
        
        switch(*choice) {
            case 49:
                createDictionary(dictionary);
                break;
            case 50:
                //dictionaryList();
                chooseDictionary(dictionary);
                break;
            default:
                printf("Saisie incorrecte ! Réessayer\n");
                break;
        }
    }while(*choice != 49 && *choice != 50);
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



void dictionaryList() {
    
    DIR* directory = opendir("/Users/berangerelatouche/Documents/fichiers_dico/");
    
    if(directory != NULL) {
        
        printf("\nChoissisez un dictionnaire:\n");
        
        struct dirent * content;
        
        while ((content = readdir(directory)) != NULL)
        {
            printf("%s\n", content->d_name);
        }
        
        closedir(directory);
        
    }else {
        closedir(directory);
    }
    
}




void createDictionary(LinkedList* dictionaryList){
    
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
    

    char* dictionaryName = malloc(sizeof(char)*255);
    printf("ENTER A NAME FOR YOUR NEW DICTIONARY\n");
    scanf("%s",dictionaryName);
    
    if(dictionaryName != NULL){
        
        FILE* newDictionary = fopen(dictionaryName,"w");
        
        if(newDictionary != NULL){
            printf("YOUR NEW DICTIONARY HAS BEEN CREATED\n");
            dictionaryList->next = newElement(dictionaryName);
            printf("HERE IS THE NEW LIST OF YOUR DICTIONARYS\n");
            printLinkedList(dictionaryList);
            printf("YOU'RE BACK TO THE MENU");
            menu(dictionaryList);
        }
        else
        {
            printf("ERROR WHILE CREATING THE NEW DICTIONARY\n");
            printf("YOU'RE BACK TO THE MENU");
            menu(dictionaryList);
        }
    }
    else{
        printf("PLEASE ENTER A VALID NAME\n");
        printf("YOU'RE BACK TO THE MENU");
        menu(dictionaryList);
    }
    
    
    dictionaryList->next = newElement(dictionaryName);

    free(dictionaryName);

}

void chooseDictionary(LinkedList* dictionary) {
    
    printLinkedList(dictionary);
    
    char* name = malloc(sizeof(char)*255);
    FILE* choosenDictionary;
    
    printf("ENTER THE NAME OF THE DICTIONARY YOU WANT TO WORK ON\n");
    scanf("%s",name);
    
    if(name != NULL){
        while(dictionary != NULL){
            if(!strcmp(name,dictionary->value)){
                choosenDictionary = fopen(name,"r+");
                if(choosenDictionary){
                    
                    menu2(choosenDictionary,dictionary);
                    
                    fclose(choosenDictionary);
                }
            }
            dictionary = dictionary->next;
        }
        
    }else{
        printf("YOU'VE ENTERED A WRONG DICTIONNARY NAME\n");
        printf("YOU'RE BACK TO THE MENU");
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

void menu2(FILE* dictionary, LinkedList* dictionaryList) {
    
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
                searchWord(dictionary,dictionaryList);
                break;
            case 2:
                //displayDictionary(dictionary,name, path,dictionaryList);
                menu2(dictionary,dictionaryList);
                break;
            case 3:
                //addWordsToDictionary(dictionary, dictionaryList);
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

//void chooseDictionary(LinkedList* dictionary) {
//    
//    char path[255] = "/Users/berangerelatouche/Documents/fichiers_dico/";
//    FILE* dictionary_choosen;
//    char* name = malloc(sizeof(char) * 255);
//    char *choice = malloc(sizeof(char));
//    
//    printf("\nVeuillez entrer le nom du dictionnaire souhaité:\n");
//    scanf("%s",name);
//    
//    strcat(name,".txt");
//    strcat(path, name);
//    
//    dictionary_choosen = fopen(path, "r+");
//    
//    if(dictionary_choosen != NULL) {
//        
//        menu2(dictionary_choosen,name,path,dictionary);
//        fclose(dictionary_choosen);
//        
//    }else {
//        
//        do {
//            printf("Le dictionnaire demandé n'existe pas\nVoulez-vous créer un dictionnaire ? o/n\n");
//            scanf("%s",choice);
//            printf("\n");
//            
//            switch (*choice) {
//                case 111:
//                    createDictionary(dictionary);
//                    break;
//                case 110:
//                    chooseDictionary(dictionary);
//                    break;
//                default:
//                    printf("Saisie incorrect ! Réessayer\n");
//                    break;
//            }
//        }while(*choice != 111 && *choice != 110);
//        
//        fclose(dictionary_choosen);
//    }
//    
//}



void searchWord(FILE* dictionary, LinkedList* dictionaryList){
    
    char *wordToFind = malloc(sizeof(char)*255);
    char *answer = malloc(sizeof(char)*1026);
    
    int lineCounter = 0;
    
    if(dictionary != NULL){
        
        printf("PLEASE ENTER THE WORD YOU WOULD LIKE TO FIND\n");
        scanf("%s",wordToFind);
        
        while(fgets(answer, 255, dictionary)){
            lineCounter++;
            answer[strcspn(answer, "\n")] = '\0';
            if(!strcmp(answer, wordToFind)){
                printf("%s HAS BEEN FOUND AT LINE NUMBER %d\n",answer,lineCounter);
                menu2(dictionary, dictionaryList);
            }
        }
        
        fclose(dictionary);
        free(answer);
        free(wordToFind);
    }
    else
        printf("ERROR WHILE OPENING THE DICTIONARY\n");
        menu(dictionaryList);
    
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

//void addWordsToDictionary(FILE * dictionary, char* name, char* path,LinkedList* dictionaryList) {
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




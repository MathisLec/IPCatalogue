#include <stdio.h>
#include <stdlib.h>

int IP_NUM = 3;
int IP_LENGTH = 15;

char** importData(){
    char** IP = malloc(sizeof(char*) * IP_NUM);
    for(int i = 0;i<IP_NUM;i++){
        IP[i] = malloc(sizeof(char) * IP_LENGTH);
    }
    return IP;
}

void clean(char** IP){
    for(int i=0;i<IP_NUM;i++){
        free(IP[i]);
    }
    free(IP);
}

void printMenu(){
    //IP 17 | MASQUE 17 | IP BINAIRE 47 | M BINAIRE 47 | IP HEXA 13 | M HEXA 13 | Type 10
    printf("Bienvenue dans IPCatalogue\n\n");
    printf(" ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ \n");
    printf("|        IP       |      MASQUE     |                                          BINAIRE                                                |             HEXA            |   TYPE   |\n");
    printf(" ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ \n");
    for(int i=0;i<IP_NUM;i++){

    }
    printf("1. Rentrer une IP\n");
    printf("2. Filtrer les IP par masque\n");
    printf("3. Quitter\n");
}

int main(){
    char** IP = importData();
    int choice;
    while(1){
        //Clear console
        printf("\e[1;1H\e[2J");
        //Print menu in console
        printMenu();
        //Get user choice
        scanf("%d",&choice);

        switch(choice){
            case 1:
                printf("Hello\n");
                break;
            case 2:
                printf("Hello\n");
                break;
            case 3:
                clean(IP);
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Veuillez choisir un écrire le numéro parmis les options proposés.\n");
                break;
        }
    }
}
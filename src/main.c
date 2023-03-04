#include "IP.h"
#include <string.h>

int IP_NUM = 0;

IP* FILTERED_IPS = NULL;
int FILTERED_IP_NUM = 0;

IP* importData(){
    char chaine[20] = "";
    FILE* myFile = fopen("save.csv","r");
    IP* IPList = NULL;
    if(myFile != NULL){
        //Get the number of IP in the file
        fgets(chaine,20,myFile);
        //Transform string into integer
        int list_length = atoi(chaine);
        //Set the number of IP in the global variable
        IP_NUM = list_length;
        //Memory alloc
        IPList = malloc(sizeof(IP) * list_length);
        //Add all IPs in the list
        for(int i=0;i<list_length;i++){
            fgets(chaine,20,myFile);
            IPList[i] = getIPObject(chaine);
        }
        //Close the file only if it exist
        fclose(myFile);
    }
    return IPList;
}

void saveData(IP* IPs){
    IP* arrayToSave = IPs;
    int nbIPInArray = IP_NUM;
    //Switch to Filtered IP Array if set
    if(FILTERED_IP_NUM > 0){
        arrayToSave = FILTERED_IPS;
        nbIPInArray = FILTERED_IP_NUM;
    }
    FILE* myFile = fopen("save.csv","w+");
    //Transform global variable into string
    char nbIPStr[11] = "";
    sprintf(nbIPStr, "%d\n", nbIPInArray);
    //Put it in the file
    fputs(nbIPStr, myFile);
    //Put IPs only if the list is not empty
    if(IPs != NULL){
        for(int i=0;i<nbIPInArray;i++){
            //Transform IP object into string representation for save
            char* ipFormated = formatIPToSaveFormat(arrayToSave[i]);
            //Put IP in the file
            fputs(ipFormated, myFile);
            free(ipFormated);
        }
    }
    fclose(myFile);
}

void clean(IP* IP){
    if(IP != NULL){
        //Free all IPs objects
        for(int i=0;i<IP_NUM;i++){
            freeIpObject(IP[i]);
        }
        //Free the array
        free(IP);
    }
}

IP* addIPInArray(IP* ips, char* ip){
    IP_NUM++;
    //Realloc memory with n+1 object in the array
    ips = realloc(ips, sizeof(IP) * IP_NUM);
    //Put the new object in the end of array
    ips[IP_NUM-1] = getIPObject(ip);
    return ips;
}

IP* addIpMenu(IP* ips){
    char* buff = calloc(20, sizeof(char));
    printf("Votre IP à ajouter (Ex:192.168.0.1/24):\n");
    //Get the user entry
    printf(">");
    scanf("%s",buff);
    //Get the new IP array
    ips = addIPInArray(ips,buff);
    free(buff);
    return ips;
}

void ipFilter(IP* ips, int mask){
    //If a filter is already set
    if(FILTERED_IPS != NULL)
        free(FILTERED_IPS);
    //Get binary mask
    char* binMask = numberIntToBinaryMask(mask);
    int nbFilteredIP = 0;
    //Add matching IP in the list
    for(int i=0;i<IP_NUM;i++){
        if(strcmp(ips[i]->mask_binary,binMask) == 0){
            nbFilteredIP++;
            FILTERED_IPS = realloc(FILTERED_IPS, sizeof(IP) * nbFilteredIP);
            FILTERED_IPS[nbFilteredIP-1] = ips[i];
        }
    }
    FILTERED_IP_NUM = nbFilteredIP;
}

void filterIpMenu(IP* ips){
    if(ips != NULL){
        printf("Votre masque pour filtrer les IP(Ex:24):\n");
        int mask;
        printf(">");
        scanf("%d",&mask);
        ipFilter(ips, mask);
    }
    else
        printf("On ne peut pas filtrer une liste vide\n");
}

void printMenu(IP* IPs){
    printf("Bienvenue dans IPCatalogue\n\n");
    printf(" ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
    printf("|\tIP\t|\tMASQUE\t\t|\t\t\t\t\tBINAIRE\t\t\t\t\t|\t\tHEXA\t\t|\tTYPE\t|\n");
    printf(" ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ \n");
    if(IPs != NULL){
        //Switch to Filtered IP Array if set
        IP* arrayToPrint = IPs;
        int nbIPInArray = IP_NUM;
        if(FILTERED_IP_NUM > 0){
            arrayToPrint = FILTERED_IPS;
            nbIPInArray = FILTERED_IP_NUM;
        }
        for(int i=0;i<nbIPInArray;i++){
            IP current = arrayToPrint[i];
            printf("|%s\t|%s   \t|%s / %s\t|%s / %s\t|%s  \t|\n",current->ip_dec,
                                                    current->mask_dec,
                                                    current->ip_binary,
                                                    current->mask_binary,
                                                    current->ip_hex,
                                                    current->mask_hex,
                                                    getStrType(current->type));
            printf(" ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ \n");
        }
    }
    printf("1. Rentrer une IP\n");
    printf("2. Filtrer les IP par masque\n");
    printf("3. Sauvegarder\n");
    printf("4. Quitter\n");
}

int main(){
    IP* IPs = importData();
    int choice;
    while(1){
        //Clear console
        printf("\e[1;1H\e[2J");
        //Print menu in console
        printMenu(IPs);
        //Get user choice
        printf(">");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                IPs = addIpMenu(IPs);
                saveData(IPs);
                break;
            case 2:
                filterIpMenu(IPs);
                break;
            case 3:
                saveData(IPs);
                printf("Données sauvegardés\n");
                break;
            case 4:
                clean(IPs);
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Veuillez choisir et écrire le numéro parmis les options proposés.\n");
                break;
        }
    }
}
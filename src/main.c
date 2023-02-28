#include "IP.h"

int IP_NUM = 3;
int IP_LENGTH = 15;

IP* importData(){
    IP* IP = malloc(sizeof(IP) * IP_NUM);
    for(int i = 0;i<IP_NUM;i++){
        IP[i] = getIPObject("192.168.0.1/24");
    }
    return IP;
}

void clean(IP* IP){
    for(int i=0;i<IP_NUM;i++){
        freeIpObject(IP[i]);
    }
    free(IP);
}

char* formatStrLineFromIp(IP i){

}

IP* addIPInArray(IP* ips, char* ip){
    IP_NUM++;
    ips = realloc(ips, sizeof(IP) * IP_NUM);
    ips[IP_NUM-1] = getIPObject(ip);
    return ips;
}

IP* addIpMenu(IP* ips){
    char* buff = calloc(20, sizeof(char));
    printf("Votre IP à ajouter (Ex:192.168.0.1/24):\n");
    scanf("%s",buff);
    ips = addIPInArray(ips,buff);
    free(buff);
    return ips;
}

void printMenu(IP* IPs){
    printf("Bienvenue dans IPCatalogue\n\n");
    printf(" ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
    printf("|\tIP\t|\tMASQUE\t\t|\t\t\t\t\tBINAIRE\t\t\t\t\t|\t\tHEXA\t\t|\tTYPE\t|\n");
    printf(" ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ \n");
    for(int i=0;i<IP_NUM;i++){
        IP current = IPs[i];
        printf("|%s\t|%s\t\t|%s / %s\t|%s / %s\t|%s\t\t|\n",current->ip_dec,
                                                current->mask_dec,
                                                current->ip_binary,
                                                current->mask_binary,
                                                current->ip_hex,
                                                current->mask_hex,
                                                getStrType(current->type));
        printf(" ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ \n");
    }
    printf("1. Rentrer une IP\n");
    printf("2. Filtrer les IP par masque\n");
    printf("3. Quitter\n");
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
        scanf("%d",&choice);

        switch(choice){
            case 1:
                IPs = addIpMenu(IPs);
                break;
            case 2:
                printf("Hello\n");
                break;
            case 3:
                clean(IPs);
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Veuillez choisir et écrire le numéro parmis les options proposés.\n");
                break;
        }
    }
}
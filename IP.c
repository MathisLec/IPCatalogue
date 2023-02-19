#include <string.h>
#include "commons.h"
#include "IP.h"

const char* DELIMITER_IP = ".";
const char* DELIMITER_MSK = "/";

void numberToBinaryMask(char* maskNumber,char* mask_binary, int numCharBinaryMask){
    int number = atoi(maskNumber);
    for(int i=1;i<numCharBinaryMask;i++){
        if(i%9==0){
            strcat(mask_binary, DELIMITER_IP);
        }
        else{
            strcat(mask_binary, number > 0 ? "1" : "0");
            number--;
        }
    }
}

IP getIPObject(char* ip){
    IP ipObj = malloc(sizeof(struct IP));
    //Field allocation
    //Decimal IP
    //Decimal Mask
    int numCharDecMask = 16; // 16 = 3 bits * 4 + 3 dots + nullbyte
    ipObj->mask_dec = malloc(sizeof(char) * numCharDecMask);

    //Binary IP
    //Binary Mask
    int numCharBinaryMask = 36; // 36 = 8 bits * 4 + 3 dots + nullbyte
    ipObj->mask_binary = malloc(sizeof(char) * numCharBinaryMask);

    //Hexa IP
    //Hexa Mask
    int numCharHexMask = 12; // 12 = 2 bits * 4 + 3 dots + nullbyte
    ipObj->mask_hex = malloc(sizeof(char) * numCharHexMask);

    //To perform modifications on string
    char* ip_copy = strdup(ip);
    //Get two parts of the ip (ip/mask)
    //Get IP
    char* token = strtok(ip_copy,DELIMITER_MSK);
    //Set ip_dec to ipObj with a copy of the content
    ipObj->ip_dec = strdup(token);
    printf("%s\n",ipObj->ip_dec);
    //Get mask
    token = strtok(NULL,DELIMITER_MSK);
    //Convert mask number into its binary representation
    numberToBinaryMask(strdup(token),ipObj->mask_binary,numCharBinaryMask);
    printf("Masque binaire: %s\n",ipObj->mask_binary);

    //convert each doted-parts from binary to dec and hex
    char* binary_cpy = strdup(ipObj->mask_binary);
    token = strtok(binary_cpy,DELIMITER_IP);
    int nbDots = 0;
    while ( token != NULL ) {
        char* dec = binaryToDec(token);
        char* hex = binaryToHex(token);
        
        strcat(ipObj->mask_dec,dec);
        strcat(ipObj->mask_hex,hex);

        free(dec);
        free(hex);
        if(nbDots<3){
            strcat(ipObj->mask_dec,DELIMITER_IP);
            strcat(ipObj->mask_hex,DELIMITER_IP);
        }
        nbDots++;
        token = strtok ( NULL, DELIMITER_IP );
    }
    printf("Masque decimal: %s\n",ipObj->mask_dec);
    printf("Masque hex: %s\n",ipObj->mask_hex);
    free(binary_cpy);
    //Stubs
    ipObj->ip_binary = NULL;

    ipObj->ip_hex = NULL;

    ipObj->type = PUBLIC;

    return ipObj;
}

void freeIpObject(IP ip){
    free(ip->ip_dec);
    free(ip->mask_dec);
    //free(ip->ip_binary);
    free(ip->mask_binary);
    //free(ip->ip_hex);
    free(ip->mask_hex);
    free(ip);
}
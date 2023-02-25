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
    int numCharDecFormat = 16; // 16 = 3 bits * 4 + 3 dots + nullbyte
    //decimal IP allocated by strdup
    //Decimal Mask
    ipObj->mask_dec = malloc(sizeof(char) * numCharDecFormat);

    //Binary IP
    int numCharBinFormat = 36; // 36 = 8 bits * 4 + 3 dots + nullbyte
    ipObj->ip_binary = malloc(sizeof(char) * numCharBinFormat);
    //Binary Mask
    ipObj->mask_binary = malloc(sizeof(char) * numCharBinFormat);

    //Hexa IP
    int numCharHexFormat = 12; // 12 = 2 bits * 4 + 3 dots + nullbyte
    ipObj->ip_hex = malloc(sizeof(char) * numCharHexFormat);
    //Hexa Mask
    ipObj->mask_hex = malloc(sizeof(char) * numCharHexFormat);

    //To perform modifications on string
    char* ip_copy = strdup(ip);
    //Get two parts of the ip (ip/mask)
    //Get IP
    char* token = strtok(ip_copy,DELIMITER_MSK);
    //Set ip_dec to ipObj with a copy of the content
    ipObj->ip_dec = strdup(token);
    //Get mask
    token = strtok(NULL,DELIMITER_MSK);
    //Convert mask number into its binary representation
    numberToBinaryMask(strdup(token),ipObj->mask_binary,numCharBinFormat);
    {
    //convert each doted-parts from binary to dec and hex
    char* binary_cpy = strdup(ipObj->mask_binary);
    token = strtok(binary_cpy,DELIMITER_IP);
    int nbDots = 0;
    while ( token != NULL ) {
        char* dec = binaryStrToDecStr(token);
        char* hex = binaryStrToHexStr(token);
        
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
    free(binary_cpy);
    }
    {
    //IP part
    //convert each doted-parts from binary to dec and hex
    char* dec_cpy = strdup(ipObj->ip_dec);
    token = strtok(dec_cpy,DELIMITER_IP);
    int nbDots = 0;
    while ( token != NULL ) {
        char* bin = decimalStrToBinaryStr(token);
        char* hex = decimalStrToHexStr(token);
        
        strcat(ipObj->ip_binary,bin);
        strcat(ipObj->ip_hex,hex);

        free(bin);
        free(hex);
        if(nbDots<3){
            strcat(ipObj->ip_binary,DELIMITER_IP);
            strcat(ipObj->ip_hex,DELIMITER_IP);
        }
        nbDots++;
        token = strtok ( NULL, DELIMITER_IP );
    }
    free(dec_cpy);
    }
   
    //Stubs
    ipObj->type = PUBLIC;

    return ipObj;
}

void freeIpObject(IP ip){
    free(ip->ip_dec);
    free(ip->mask_dec);
    free(ip->ip_binary);
    free(ip->mask_binary);
    free(ip->ip_hex);
    free(ip->mask_hex);
    free(ip);
}
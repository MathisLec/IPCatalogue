#include <string.h>
#include "IP.h"

const char* DELIMITER_IP = ".";
const char* DELIMITER_MSK = "/";
char* TYPE_STR[5] = {"PUBLIC", "PRIVATE", "LOOPBACK", "NETWORK", "BROADCAST"};
int NUM_CHAR_DEC_FORMAT = 16; // 16 = 3 bits * 4 + 3 dots + nullbyte
int NUM_CHAR_BIN_FORMAT = 36; // 36 = 8 bits * 4 + 3 dots + nullbyte
int NUM_CHAR_HEX_FORMAT = 12; // 12 = 2 bits * 4 + 3 dots + nullbyte

/**
 * numberToBinaryMask(char* maskNumber,char* mask_binary)
 * maskNumber: mask number in string format
 * mask_binary: receive binary representation in string format
*/
void numberToBinaryMask(char* maskNumber,char* mask_binary){
    int number = atoi(maskNumber);
    for(int i=1;i<NUM_CHAR_BIN_FORMAT;i++){
        if(i%9==0){
            strcat(mask_binary, DELIMITER_IP);
        }
        else{
            strcat(mask_binary, number > 0 ? "1" : "0");
            number--;
        }
    }
}

/**
 * numberIntToBinaryMask(int mask)
 * mask: mask number
 * return: the string representation of the mask in binary format
*/
char* numberIntToBinaryMask(int mask){
    char maskNbStr[2] = "";
    sprintf(maskNbStr, "%d", mask);
    char* binMask = calloc(NUM_CHAR_BIN_FORMAT,sizeof(char));
    numberToBinaryMask(maskNbStr,binMask);
    return binMask;
}

int binaryMaskToNumber(char* binaryMask){
    int cmp = 0;
    int index = 0;
    while(binaryMask[index] != '0' && binaryMask[index] != '\0' ){
        if(binaryMask[index] != '.')
            cmp++;
        index++;
    }
    return cmp;
}

/**
 * void printIPObj(IP ip)
 * ip: the ip object to print
*/
void printIPObj(IP ip){
    printf("\n---------- IP ----------\n");
    printf("Decimal----------\n");
    printf("IP: %s\n",ip->ip_dec);
    printf("Masque: %s\n",ip->mask_dec);
    printf("Hexa----------\n");
    printf("IP: %s\n",ip->ip_hex);
    printf("Masque: %s\n",ip->mask_hex);
    printf("Binary----------\n");
    printf("IP: %s\n",ip->ip_binary);
    printf("Masque: %s\n",ip->mask_binary);
    printf("\n");
}

/**
 * void convertAndFormatAdress(char* toConvert,
 *                              char* firstFormat, char* secondFormat,
 *                              char* (*firstConversionFunction)(char*),char* (*secondConversionFunction)(char*))
 * toConvert: string to convert
 * firstFormat: reveive the first format representation
 * secondFormat: reveive the second format representation
 * firstConversionFunction: pointer of the first conversion function
 * secondConversionFunction: pointer of the second conversion function
*/
void convertAndFormatAdress(char* toConvert, 
                            char* firstFormat, 
                            char* secondFormat,
                            char* (*firstConversionFunction)(char*),
                            char* (*secondConversionFunction)(char*)){
    //convert each doted-parts from toConvert to firstFormat and secondFormat
    char* toConvert_cpy = strdup(toConvert);
    char* token = strtok(toConvert_cpy,DELIMITER_IP);
    int nbDots = 0;
    while ( token != NULL ) {
        //Use conversion functions
        char* firstConversion = firstConversionFunction(token);
        char* secondConversion = secondConversionFunction(token);
        //Concat parts after parts
        strcat(firstFormat,firstConversion);
        strcat(secondFormat,secondConversion);
        // clean to mitigate memory leaks
        free(firstConversion);
        free(secondConversion);
        //Add point delimiter
        if(nbDots<3){
            strcat(firstFormat,DELIMITER_IP);
            strcat(secondFormat,DELIMITER_IP);
        }
        nbDots++;
        token = strtok ( NULL, DELIMITER_IP );
    }
    free(toConvert_cpy);
}

char* formatIPToSaveFormat(IP ip){
    char* finalStr = calloc(16,sizeof(char));
    strcat(finalStr, ip->ip_dec);
    strcat(finalStr, "/");
    char nbIPStr[2] = "";
    sprintf(nbIPStr, "%d", binaryMaskToNumber(ip->mask_binary));
    strcat(finalStr, nbIPStr);
    strcat(finalStr, "\n\0");
    return finalStr;
}

/**
 * IP ipObjAllocation()
 * return: IP object well allocated, except ip_dec field which is allocated just after by strdup
*/
IP ipObjAllocation(){
    IP ipObj = malloc(sizeof(struct IP));
    //Field allocation
    //Decimal IP
    //decimal IP allocated by strdup
    //Decimal Mask
    ipObj->mask_dec = calloc(NUM_CHAR_DEC_FORMAT, sizeof(char));

    //Binary IP
    ipObj->ip_binary = calloc(NUM_CHAR_BIN_FORMAT, sizeof(char));
    //Binary Mask
    ipObj->mask_binary = calloc(NUM_CHAR_BIN_FORMAT, sizeof(char));

    //Hexa IP
    ipObj->ip_hex = calloc(NUM_CHAR_HEX_FORMAT, sizeof(char));
    //Hexa Mask
    ipObj->mask_hex = calloc(NUM_CHAR_HEX_FORMAT, sizeof(char));
    return ipObj;
}

/**
 * IP getIPObject(char* ip)
 * ip: ip string representation "xxx.xxx.xxx.xxx/yy"
 * return: IP object from string representation
*/
IP getIPObject(char* ip){
    IP ipObj = ipObjAllocation();
    //To perform modifications on string
    char* ip_copy = strdup(ip);
    //Get two parts of the ip (ip/mask)
    //Get IP
    char* token = strtok(ip_copy,DELIMITER_MSK);
    //Set ip_dec to ipObj with a copy of the content
    ipObj->ip_dec = strdup(token);
    //Get mask
    token = strtok(NULL,DELIMITER_MSK);
    char* mask_tok = strdup(token);

    //Quit if mask too large
    if(atoi(mask_tok)>32){
        free(mask_tok);
        printf("Bad mask\n");
        exit(EXIT_FAILURE);
    }

    //Convert mask number into its binary representation
    numberToBinaryMask(mask_tok,ipObj->mask_binary);
    free(mask_tok);

    //Convert from decimal IP to binary and hexa IP
    convertAndFormatAdress(ipObj->ip_dec,ipObj->ip_binary,ipObj->ip_hex,decimalStrToBinaryStr,decimalStrToHexStr);
   
    //Convert from binary mask to decimal and hexa mask
    convertAndFormatAdress(ipObj->mask_binary,ipObj->mask_dec,ipObj->mask_hex,binaryStrToDecStr,binaryStrToHexStr);

    //Stubs
    ipObj->type = PUBLIC;

    return ipObj;
}

/**
 * void freeIpObject(IP ip)
 * ip: the ip object to free
*/
void freeIpObject(IP ip){
    free(ip->ip_dec);
    free(ip->mask_dec);
    free(ip->ip_binary);
    free(ip->mask_binary);
    free(ip->ip_hex);
    free(ip->mask_hex);
    free(ip);
}

/**
 * char* getStrType(type t)
 * t: the type to return as string
 * return: the type in string representation
*/
char* getStrType(type t){
    return TYPE_STR[t];
}
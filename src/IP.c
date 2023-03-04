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

int numberOfOneInMask(char* mask){
    int cmp = 0;
    int index = 0;
    while(mask[index] != '0' && index < NUM_CHAR_BIN_FORMAT-4){ // str format - 3 dots - nullbyte
        if(mask[index] != '.')
            cmp++;
        index++;
    }
    return cmp; // total - nbOfOne
}


unsigned long numberOfMachineFromBinary(char* address, char* mask){
    int nbOfOneInMask = numberOfOneInMask(mask);
    int nbBitInIp = NUM_CHAR_BIN_FORMAT - 4;// str format - 3 dots - nullbyte
    char machineAddressBinary[nbBitInIp - nbOfOneInMask];
    int index = nbOfOneInMask;
    int indexArray = 0;
    while(index<=NUM_CHAR_BIN_FORMAT){
        char currentBitIP = address[index];
        if(currentBitIP != '.'){
            machineAddressBinary[indexArray] = currentBitIP;
            indexArray++;
        }
        index++;
    }
    return binaryStrToDecULong(machineAddressBinary);
}

unsigned long numberOfMachine(IP ip){
    return numberOfMachineFromBinary(ip->ip_binary,ip->mask_binary);
}

char* getBoardcast(IP ip){
    char* binaryIP_copy = strdup(ip->ip_binary);
    for(int i=0;i<NUM_CHAR_BIN_FORMAT;i++){
        if(ip->mask_binary[i] == '0'){
            binaryIP_copy[i] = '1';
        }
    }
    return binaryIP_copy;
}

int isIpPublic(IP ip){
    int isIpPublic = 0;
    unsigned long publicRanges[][2] = {
        {16777216, 167772159}, //1.0.0.0-9.255.255.255
        {184549376, 1681915903}, //11.0.0.0-100.63.255.255
        {1686110208, 2130706431}, //100.128.0.0-126.255.255.255
        {2147483648, 2851995647}, //128.0.0.0-169.253.255.255
        {2852061184, 2886729727}, //169.255.0.0-172.15.255.255
        {2887778304, 3221225471}, //172.32.0.0-191.255.255.255
        {3221226240, 3227017983}, //192.0.3.0-192.88.98.255
        {3227018240, 3232235519}, //192.88.100.0-192.167.255.255
        {3232301056, 3323068415}, //192.169.0.0-198.17.255.255
        {3323199488, 3325256703}, //198.20.0.0-198.51.99.255
        {3325256960, 3405803775}, //198.51.101.0-203.0.112.255
        {3405804032, 3758096383} //203.0.114.0-223.255.255.255
    };
    int nbRange = 12;
    unsigned long ipDec = ipDecToNumber(ip->ip_dec);
    for(int i=0;i<nbRange;i++){
        if(ipDec>=publicRanges[i][0] && ipDec<=publicRanges[i][1])
            isIpPublic = 1;
    }
    //Is IP 192.0.1.0/24?
    if(strcmp(ip->ip_dec,"192.0.1.0") == 0 && strcmp(ip->mask_dec,"255.255.255.0") == 0)
        isIpPublic = 1;

    return isIpPublic;
}

type addressToType(IP ip){
    type addressType;
    unsigned long nbMachine = numberOfMachine(ip);
    long boardcastNumber = numberOfMachineFromBinary(getBoardcast(ip),ip->mask_binary);
    if(nbMachine == 0)
        addressType = NETWORK;
    else if(nbMachine == boardcastNumber)
        addressType = BROADCAST;
    else if(isIpPublic(ip))
        addressType = PUBLIC;
    else
        addressType = PRIVATE;
    return addressType;
}

/**
 * unsigned long ipDecToNumber(char* ip)
 * ip: the ip to convert
 * return: the decimal representation of the ip as an unsigned long
*/
unsigned long ipDecToNumber(char* ip){
    //The final number
    unsigned long finalNumber = 0;
    //Copy the ip to don't destruct it with strtok
    char* ip_cpy = strdup(ip);
    char* token = strtok(ip_cpy,DELIMITER_IP);
    //The main goal of this code is to perform (www * 256^3 + xxx * 256^2 + yyy * 256^1 + zzz) = ip address as number
    int power = 3;
    while(token != NULL){
        unsigned long ip_part = atoi(token);
        unsigned long powerCalc = 1;
        for(int i=0;i<power;i++)
            powerCalc *= 256;
        ip_part *= powerCalc;
        finalNumber+=ip_part;
        token = strtok(NULL,DELIMITER_IP);
        power--;
    }
    free(ip_cpy);
    return finalNumber;
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
    if(token == NULL){
        free(ip_copy);
        freeIpObject(ipObj);
        fprintf(stderr,"Bad IP\n");
        exit(EXIT_FAILURE);
    }
    char* mask_tok = strdup(token);

    //Quit if mask too large
    if(atoi(mask_tok)>32){
        free(ip_copy);
        freeIpObject(ipObj);
        free(mask_tok);
        fprintf(stderr,"Bad mask\n");
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
    ipObj->type = addressToType(ipObj);

    free(ip_copy);
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

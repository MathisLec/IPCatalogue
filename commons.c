#include "commons.h"
#include <string.h>

char* binaryToDec(char* bin){
    int dec = (int) strtol(bin,NULL,2);
    char* strDec = malloc(sizeof(char)*4);
    sprintf(strDec,"%d",dec);
    return strDec;
}

char* binaryToHex(char* bin){
    // FIRST SEMI-BYTE
    char firstPart[5];
    strncpy(firstPart,bin,4);
    firstPart[4] = '\0';
    int decFirst = (int) strtol(firstPart,NULL,2);
    //Convertion
    char* strHexFirst = malloc(sizeof(char)*3);
    sprintf(strHexFirst,"%x",decFirst);
    
    // SECOND SEMI-BYTE
    char secondPart[5];
    strncpy(secondPart,bin+4,4);
    secondPart[4] = '\0';
    int decSecond = (int) strtol(secondPart,NULL,2);
    //Convertion
    char* strHexSecond = malloc(sizeof(char)*2);
    sprintf(strHexSecond,"%x",decSecond);
    //Concat two Parts
    strcat(strHexFirst,strHexSecond);
    //Free
    free(strHexSecond);
    return strHexFirst;
}
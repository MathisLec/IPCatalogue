#include "commons.h"
#include <string.h>

/**
 * char* decimalIntToBinaryStr(int num)
 * num: decimal integer to convert
 * return: binary representation in string format
*/
char* decimalIntToBinaryStr(int num) {
    int byteSize = 8;
    char* finalString = malloc(sizeof(char)*byteSize+1);// adress part on 8 bits + nullbyte
    for(int i=7;i>=0;i--){
        if(num>0){
            finalString[i] = num%2==0 ? '0' : '1';
            num/=2;
        }
        else
            finalString[i] = '0';
    }
    return finalString;
}

/**
 * char* decimalStrToBinaryStr(char* num)
 * num: decimal string representation to convert
 * return: binary representation in string format
*/
char* decimalStrToBinaryStr(char* num) {
    int val = atoi(num);
    return decimalIntToBinaryStr(val);
}

/**
 * char* decimalIntToHexStr(int num)
 * num: decimal integer to convert
 * return: hexa representation in string format
*/
char* decimalIntToHexStr(int num) {
    char* bin = decimalIntToBinaryStr(num);
    char* hex = binaryStrToHexStr(bin);
    free(bin);
    return hex;
}

/**
 * char* decimalStrToHexStr(char* num)
 * num: decimal string representation to convert
 * return: hexa representation in string format
*/
char* decimalStrToHexStr(char* num) {
    int val = atoi(num);
    return decimalIntToHexStr(val);
}

/**
 * char* binaryStrToDecStr(char* num)
 * num: decimal string representation to convert
 * return: hexa representation in string format
*/
char* binaryStrToDecStr(char* bin){
    int dec = (int) strtol(bin,NULL,2);
    char* strDec = malloc(sizeof(char)*4);
    sprintf(strDec,"%d",dec);
    return strDec;
}

/**
 * unsigned long binaryStrToDecULong(char* bin)
 * bin: the binary string to convert
 * return: the number in unsigned long format
*/
unsigned long binaryStrToDecULong(char* bin){
    return strtoul(bin,NULL,2);
}

/**
 * char* binaryStrToHexStr(char* bin)
 * bin: binary string representation to convert
 * return: hexa representation in string format
*/
char* binaryStrToHexStr(char* bin){
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
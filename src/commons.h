#ifndef COMMONS_H
#define COMMONS_H

#include <stdio.h>
#include <stdlib.h>

char* binaryStrToDecStr(char* bin);

unsigned long binaryStrToDecULong(char* bin);

char* binaryStrToHexStr(char* bin);

char* decimalIntToBinaryStr(int num);

char* decimalStrToBinaryStr(char* num);

char* decimalIntToHexStr(int num);

char* decimalStrToHexStr(char* num);

#endif
#ifndef IP_H
#define IP_H

typedef enum { PUBLIC, PRIVATE, LOOPBACK, NETWORK, BROADCAST } type;

typedef struct IP{
    char* ip_dec;
    char* mask_dec;
    
    char* ip_binary;
    char* mask_binary;

    char* ip_hex;
    char* mask_hex;

    type type;
}* IP;

IP getIPObject(char* ip);

void freeIpObject(IP ip);

void printIPObj(IP ip);

char* getStrType(type t);

#endif
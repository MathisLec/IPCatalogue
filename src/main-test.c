#include "IP.h"
#include "commons.h"

void main(){
    /*
    char* ip = "255.255.255.255/22";
    IP i = getIPObject(ip);
    printIPObj(i);
    freeIpObject(i);
    */
   char* ip = "192.168.0.1/24";
   IP ipO = getIPObject(ip);
    numberOfMachine(ipO);
    freeIpObject(ipO);

}
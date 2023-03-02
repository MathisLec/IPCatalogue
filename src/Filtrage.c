#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>



void filter_ip(char* filename,) {
    float mask;

    scanf("%f", &mask);

    FILE *fp;
    char line[100];
    fp = fopen(filename, "r");
    while (fgets(line, sizeof(line), fp)) {
        char *ip_str = strtok(line, " \n");
        if (ip_str == NULL) {
            continue;
        }
        struct in_addr ip_addr;
        inet_pton(AF_INET, ip_str, &ip_addr);
        char *netmask_str = strtok(NULL, " \n");
        if (netmask_str == NULL) {
            continue;
        }
        struct in_addr netmask_addr;
        inet_pton(AF_INET, netmask_str, &netmask_addr);
        struct in_addr masked_ip;
        masked_ip.s_addr = ip_addr.s_addr & netmask_addr.s_addr;
        char *masked_ip_str = inet_ntoa(masked_ip);
        if (strcmp(masked_ip_str, mask) == 0) {
            printf("%s\n", ip_str);
        }
    }
    fclose(fp);
}

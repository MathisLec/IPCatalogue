enum type { PUBLIC, PRIVATE, LOOPBACK };

typedef struct IP{
    char* ip_dec;
    char* mask_dec;
    
    char* ip_binary;
    char* mask_binary;

    char* ip_hex;
    char* mask_hex;

    type type;
} IP;
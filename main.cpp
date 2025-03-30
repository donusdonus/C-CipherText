#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include "include/CipherText/CipherText.h"


CipherText cipher;
int main() {

    cipher.init();
    char data[1023];
    size_t len=0;

    uint8_t encrypt_key[CIPHER_BUFFER_SIZE];
    uint8_t decrypt_key[CIPHER_BUFFER_SIZE];

    memcpy(&encrypt_key[0],&cipher.cipher_encypt[0],CIPHER_BUFFER_SIZE);
    memcpy(&decrypt_key[0],&cipher.cipher_decypt[0],CIPHER_BUFFER_SIZE);
    
    len = sprintf(&data[0],"Hello Everyone. How are You to day.");

    //cipher.view_table("MY DATA",(uint8_t*)&data[0],len,10);

    cipher.print_array("__a",&encrypt_key[0],CIPHER_BUFFER_SIZE);

    cipher.print_array("__b",&decrypt_key[0],CIPHER_BUFFER_SIZE);

    cipher.XOR((uint8_t*)&encrypt_key[0],CIPHER_BUFFER_SIZE,12);

    cipher.XOR((uint8_t*)&decrypt_key[0],CIPHER_BUFFER_SIZE,12);

    cipher.print_array("__ae",&encrypt_key[0],CIPHER_BUFFER_SIZE);

    cipher.print_array("__bd",&decrypt_key[0],CIPHER_BUFFER_SIZE);

    printf("\n\n");
    return 0;
}

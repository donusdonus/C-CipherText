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
    
    len = sprintf(&data[0],"Little John\n");


    cipher.encrypt((uint8_t*)&data[0],len,234);
    cipher.view_table("Data Encryption",(uint8_t*)&data[0],len,10);
    cipher.decrpyt((uint8_t*)&data[0],len,234);
    cipher.view_table("Data Decryption",(uint8_t*)&data[0],len,10);

    return 0;
}
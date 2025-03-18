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
    
    len = sprintf(&data[0],"Edith Rehnborg, wife of Nutrilite founder Carl Rehnborg, founded Edith Rehnborg Cosmetics in 1958, which later became Artistry.[1] In 1972, Nutrilite merged with Amway thereby giving Amway the controlling interest of the Artistry brand.[2] The brand expanded internationally to Australia, Hong Kong, Malaysia, France, the Netherlands, United Kingdom and West Germany.\n");


    cipher.encrypt((uint8_t*)&data[0],len,234);
    cipher.view_table("Data Encryption",(uint8_t*)&data[0],len,10);
    cipher.decrpyt((uint8_t*)&data[0],len,234);
    cipher.view_table("Data Decryption",(uint8_t*)&data[0],len,10);

    return 0;
}
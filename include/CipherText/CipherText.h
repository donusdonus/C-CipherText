#ifndef CIPHERTEXT_H
#define CIPHERTEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#define windows 1
#define esp32 2
#define platform windows
#if platform == windows
    #define _print(fmt, ...) printf(fmt, ##__VA_ARGS__)
    #define _randon rand()
#elif platform == esp32
    #define print(fmt, ...) log_printf(fmt, ##__VA_ARGS__)
#endif

#define CIPHER_BUFFER_SIZE 256 
#define ischar(x) (x>=32)&&(x<127)

class CipherText
{
private:
    uint8_t cipher_encypt[CIPHER_BUFFER_SIZE];
    uint8_t cipher_decypt[CIPHER_BUFFER_SIZE];
    void cipher_table(uint8_t *pri, size_t size);
    void cipher_table_inverse(uint8_t *pri,uint8_t *sec,size_t size);
    void check_duplicates(uint8_t *buffer, uint8_t size);

public:
    void init();
    void encrypt(uint8_t *data,size_t size,int magic_number);
    void decrpyt(uint8_t *data,size_t size,int magic_number);
    void view_table(const char *table_name,uint8_t *buffer, size_t size,uint8_t mod_table);
  
};


#endif

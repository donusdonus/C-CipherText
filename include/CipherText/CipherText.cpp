#include "CipherText.h"


void CipherText::init()
{
    cipher_table(cipher_encypt,CIPHER_BUFFER_SIZE);
    cipher_table_inverse(cipher_encypt,cipher_decypt,CIPHER_BUFFER_SIZE);
}

void CipherText::cipher_table(uint8_t *pri, size_t size) {

    uint8_t numbers[CIPHER_BUFFER_SIZE]; 



    for (size_t i = 0; i < CIPHER_BUFFER_SIZE; i++) {
            numbers[i] = i;
    }

        
    for (size_t i = size - 1; i > 0; i--) {
        uint8_t j = (uint8_t)(rand() % (i + 1)); 
        uint8_t temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }


    for (size_t i = 0; i < CIPHER_BUFFER_SIZE; i++) {
            pri[i] = numbers[i];
    }
    
}

void CipherText::cipher_table_inverse(uint8_t *pri,uint8_t *sec,size_t size)
{
    for(size_t i=0;i<size;i++)
    {
        sec[pri[i]]=(uint8_t)i;
    }
}

void CipherText::check_duplicates(uint8_t *buffer, uint8_t size) {
    bool seen[256] = {false}; 

    print("Checking for duplicates...\n");
    for (uint8_t i = 0; i < size; i++) {
        if (seen[buffer[i]]) {
            print("Duplicate found: %d\n", buffer[i]);
            return;
        }
        seen[buffer[i]] = true;  
    }

}

void CipherText::decrpyt(uint8_t *data,size_t size,int magic_number)
{
    for(size_t i = 0; i < size; i++)
    {
        uint16_t temp = (data[i]-magic_number)%CIPHER_BUFFER_SIZE;
        data[i] = cipher_decypt[(uint8_t)temp];
    }
}

void CipherText::encrypt(uint8_t *data,size_t size,int magic_number)
{
    for(size_t i = 0; i < size; i++)
    {
        uint16_t temp = (cipher_encypt[(uint8_t)data[i]] + magic_number)%CIPHER_BUFFER_SIZE;
        data[i] = (uint8_t)temp;
    }
}

void CipherText::view_table(const char *table_name,uint8_t *buffer, size_t size,uint8_t mod_table) {
    uint8_t mod = mod_table;
    print("View table: %s  Size %d Bytes\n",table_name,size);
    for(size_t i = 0; i < mod; i++)
    {
        print("+---+--------");  // เส้นขอบบน
    }

    print("+\n");

    for (size_t i = 0; i < size; i++) 
    {
        char c = (char)(ischar(buffer[i])? buffer[i] : '.');
        if(((i%mod)==0) && (i>0))
        {
            
            print("|\n");
            print("|%3d| %4d %c ",i,buffer[i],c);
        } 
        else 
        {
            print("|%3d| %4d %c ",i,buffer[i],c);  
        }
    }
    print("|\n");

    for(uint8_t i = 0; i < mod; i++)
    {
        print("+---+--------"); 
    }

    print("+\n");
}

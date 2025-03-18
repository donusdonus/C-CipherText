#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>
#include <string>

class Serial {
private:
    HANDLE hSerial;
    bool connected;

public:
    Serial(const std::string& portName, 
           DWORD baudRate = CBR_9600, 
           BYTE dataBits = 8, 
           BYTE parity = NOPARITY, 
           BYTE stopBits = ONESTOPBIT);
    ~Serial();

    bool isConnected();
    int available(); // เช็คจำนวนไบต์ที่รออยู่ในบัฟเฟอร์
    int readData(char* buffer, unsigned int nbChar);
    int readBytes(char* buffer, int length);
    bool writeData(const char* buffer, unsigned int nbChar);
    void flush();
    void close();
};

#endif

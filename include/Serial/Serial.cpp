#include "Serial.h"
#include <iostream>

Serial::Serial(const std::string& portName, DWORD baudRate, BYTE dataBits, BYTE parity, BYTE stopBits) {
    connected = false;

    hSerial = CreateFileA(portName.c_str(),
                          GENERIC_READ | GENERIC_WRITE,
                          0, // No sharing
                          NULL, // No security
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL,
                          NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to open " << portName << std::endl;
        return;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error: Unable to get COM state." << std::endl;
        CloseHandle(hSerial);
        return;
    }

    // ตั้งค่าพารามิเตอร์ของ Serial Port
    dcbSerialParams.BaudRate = baudRate;
    dcbSerialParams.ByteSize = dataBits;
    dcbSerialParams.Parity = parity;
    dcbSerialParams.StopBits = stopBits;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error: Unable to set COM state." << std::endl;
        CloseHandle(hSerial);
        return;
    }

    connected = true;
}

Serial::~Serial() {
    close();
}

bool Serial::isConnected() {
    return connected;
}

// ฟังก์ชันเช็คจำนวนไบต์ที่รออยู่ในบัฟเฟอร์
int Serial::available() {
    if (!connected) return 0;

    DWORD errors;
    COMSTAT status;
    if (ClearCommError(hSerial, &errors, &status)) {
        return status.cbInQue; // คืนค่าจำนวนไบต์ที่รอในบัฟเฟอร์
    } else {
        return 0;
    }
}

// อ่านข้อมูลตามจำนวนไบต์ที่ต้องการ
int Serial::readBytes(char* buffer, int length) {
    DWORD bytesRead;
    int totalRead = 0;

    while (totalRead < length) {
        DWORD bytesToRead = length - totalRead;
        if (!ReadFile(hSerial, buffer + totalRead, bytesToRead, &bytesRead, NULL)) {
            return totalRead;
        }
        totalRead += bytesRead;
    }
    return totalRead;
}

// อ่านข้อมูลแบบเดิม
int Serial::readData(char* buffer, unsigned int nbChar) {
    DWORD bytesRead;
    if (!ReadFile(hSerial, buffer, nbChar, &bytesRead, NULL)) {
        return 0;
    }
    return bytesRead;
}

// เขียนข้อมูลไปยัง COM Port
bool Serial::writeData(const char* buffer, unsigned int nbChar) {
    DWORD bytesSent;
    return WriteFile(hSerial, buffer, nbChar, &bytesSent, NULL) && bytesSent == nbChar;
}

// ล้างบัฟเฟอร์ข้อมูลที่รออ่าน
void Serial::flush() {
    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
}

// ปิดการเชื่อมต่อ Serial
void Serial::close() {
    if (connected) {
        CloseHandle(hSerial);
        connected = false;
    }
}

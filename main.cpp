#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

class Checksum {
public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
        unsigned short sum = 0;
        for (unsigned int i = 0; i < message.size(); i++) {
            sum += message[i];
        }
        return sum;
    }

    virtual bool doChecksum(std::vector<unsigned char> message, unsigned short checksumValue) {
        return (checksumValue == calcChecksum(message));
    }

    virtual void appendChecksum(std::vector<unsigned char>& message, unsigned int numBytes) {
        unsigned short checksumValue = calcChecksum(message);
        std::vector<unsigned char> checksumBytes(numBytes, 0); 
        for (unsigned int i = 0; i < numBytes; i++) {
            checksumBytes[i] = (checksumValue >> (8 * i)) & 0xFF; 
        }
        message.insert(message.end(), checksumBytes.begin(), checksumBytes.end());
    }
};  

class ChecksumXOR : public Checksum {
public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) override {
        unsigned char resultadoXor = 0;
        for (unsigned int i = 0; i < message.size(); i++) {
            resultadoXor ^= message[i];
        }
        return resultadoXor;
    }

    virtual void appendChecksum(std::vector<unsigned char>& message, unsigned int numBytes) override {
        unsigned char checksumValue = calcChecksum(message);
        message.push_back(checksumValue);  
    }
};

int main() {
    Checksum checksum;
    std::vector<unsigned char> vec = { 'H', 'e', 'l', 'l', 'o' };
    checksum.appendChecksum(vec, 2); 

    printf("Mensagem com checksum: ");
    for (auto ch : vec) {
        printf("%u ", ch);
    }   
    printf("\n");

    ChecksumXOR checksumXor;
    std::vector<unsigned char> vecXor = { 'H', 'e', 'l', 'l', 'o' };
    checksumXor.appendChecksum(vecXor, 2); 
    
    printf("Mensagem com checksum XOR: ");
    for (auto ch : vecXor) {
        printf("%u ", ch);
    }
    printf("\n");

    return 0;
}

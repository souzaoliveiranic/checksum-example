#include <stdio.h>
#include <vector>
#include <string>

class Checksum {
public:
    virtual unsigned int calcChecksum(std::string message) {
        unsigned int sum = 0;
        for(unsigned int i = 0; i < message.size(); i++) {
            sum += message[i];
        } 
        return sum;
    }

    virtual bool doChecksum(std::string message, unsigned int checksumValue) {
        return (checksumValue == calcChecksum(message));
    }

    virtual unsigned int calcChecksum(std::vector<unsigned char> message) {
        unsigned int sum = 0;
        for(unsigned int i = 0; i < message.size(); i++) {
            sum += message[i];
        } 
        return sum;
    }

    virtual bool doChecksum(std::vector<unsigned char> message, unsigned int checksumValue) {
        return (checksumValue == calcChecksum(message));
    }
};

class MyChecksum : public Checksum {
public:
    unsigned int calcChecksum(std::vector<unsigned char> message) override {
        unsigned int sum = 0;

        if (message.size() % 2 != 0) {
            message.push_back(0x00);  
        }

        for (size_t i = 0; i < message.size(); i += 2) {
            unsigned short palavra = (message[i] << 8) | message[i + 1]; 
            sum += palavra;
        }

        return sum & 0xFFFF; 
    }
    
    unsigned int calcChecksum(std::string message) override {
        std::vector<unsigned char> byteMessage(message.begin(), message.end());
        return calcChecksum(byteMessage); 
    }
};

int main() {
    MyChecksum checksum;

    std::string str = "Hello, World!";
    printf("Checksum de '%s' é %u\n", str.c_str(), checksum.calcChecksum(str));

    std::vector<unsigned char> vec = {'H', 'e', 'l', 'l', 'o'};
    printf("Checksum do vetor é %u\n", checksum.calcChecksum(vec));

    return 0;
}

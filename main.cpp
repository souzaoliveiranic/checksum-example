#include <stdio.h>
#include <vector>
#include <string>

class Checksum {

public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
        unsigned short sum = 0;
        for (unsigned int i = 0; i < message.size(); i++) {
            sum += message[i];
        }
        return sum;
    }

    void addChecksum(std::vector<unsigned char>& message, unsigned short checksumValue) {
        char LSB = checksumValue & 0xFF;     
        char MSB = (checksumValue >> 8) & 0xFF;
        message.push_back(MSB);
        message.push_back(LSB);
    }

    virtual bool doChecksum(std::vector<unsigned char> message, unsigned short checksumValue) {
        return (checksumValue == calcChecksum(message));
    }
};

class ChecksumXOR: public Checksum {
    public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
        unsigned char resultadoXor = 0;
        for(unsigned int i=0; i<message.size(); i++){
            if(i==0) resultadoXor = message[i];
            else resultadoXor = resultadoXor^message[i];
        }
        return resultadoXor;
    }
};

int main() {

    Checksum checksum;
    std::vector<unsigned char> vec = { 'H','e','l','l','o' };
    printf("Checksum is %u\n", checksum.calcChecksum(vec));

    ChecksumXOR checksumXOR;
    printf("Checksum is %u\n", checksumXOR.calcChecksum(vec));

    checksum.addChecksum(vec,checksum.calcChecksum(vec));
    for(unsigned int i=0; i<vec.size(); i++){
        printf(" %u", vec[i]);
    }

    return 0;
}


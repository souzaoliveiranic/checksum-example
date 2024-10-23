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

    virtual bool doChecksum(std::vector<unsigned char> message, unsigned short checksumValue) {
        return (checksumValue == calcChecksum(message));
    }
};

class ChecksumXOR : public Checksum {
public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
        unsigned char resultadoXor = 0;
        for (unsigned int i = 0; i < message.size(); i++) {
            if (i == 0) {
                resultadoXor = message[i];
            }
            else {
                resultadoXor = resultadoXor ^ message[i];
            }
        }
        return resultadoXor;
    }
};

//i=0 resultadoXor = message[0];
//i=1 resultadoXor = message[0] ^ message[1];
//i=2 resultadoXor = resultadoXor ^ message[2];

int main() {

    Checksum checksum;
    std::vector<unsigned char> vec = { 'H','e','l','l','o' };
    printf("Checksum is %u\n", checksum.calcChecksum(vec));

    ChecksumXOR checksumXOR;
    printf("Checksum is %u\n", checksumXOR.calcChecksum(vec));
    return 0;

}


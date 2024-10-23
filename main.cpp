#include <stdio.h>
#include <vector>
#include <string>

// Teste teste

class Checksum {
public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
        unsigned int sum = 0;
        for (int i = 0; i < message.size(); i++) {
            sum += message[i];
        }
        return sum;
    }

    virtual bool doChecksum(std::vector<unsigned char> message, unsigned int checksumValue) {
        return (checksumValue == calcChecksum(message));
    }
};
class ChecksumXOR : public Checksum {
public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
        unsigned char resultadoXOR = 0;
        for (unsigned int i = 0; i < message.size(); i++) {
            if (i == 0) {
                resultadoXOR = message[i];
            }
            else {
                resultadoXOR = resultadoXOR ^ message[i];
            }

        }
        return resultadoXOR;
    }
};

int main() {

    Checksum checksum;

    std::vector<unsigned char> vec = { 'H','e','l','l','o' };
    printf("Checksum is %u\n", checksum.calcChecksum(vec));
    return 0;
}
#include <stdio.h>
#include <vector>
#include <string>

class Checksum {
public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
        unsigned short sum = 0;
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
        unsigned short resultadoXor = 0;
        for (unsigned int i = 0; i < message.size(); i++) {
            if (i == 0){
                resultadoXor = message[i];
            }
            else {
                resultadoXor ^= message[i];
            }
        }
        return resultadoXor;
    }
};

int main() {
    Checksum checksum;
    std::vector<unsigned char> vec1 = {'H', 'e', 'l', 'l', 'o'};
    printf("Checksum is %u\n", checksum.calcChecksum(vec1));

    ChecksumXOR checksumXOR;
    std::vector<unsigned char> vec2 = {'H', 'e', 'l', 'l', 'o'};
    printf("Checksum is %u\n", checksumXOR.calcChecksum(vec2));

    return 0;
}

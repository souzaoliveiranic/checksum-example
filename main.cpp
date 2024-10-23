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

    std::vector<unsigned char> appendChecksum(std::vector<unsigned char> message, size_t checksumBytes) {
        unsigned short checksum = calcChecksum(message);
        std::vector<unsigned char> checksumVector(checksumBytes, 0);
        for (unsigned int i = 0; i < checksumBytes; i++) {
            checksumVector[checksumBytes - 1 - i] = (checksum >> (8 * i)) & 0xFF;
        }
        message.insert(message.end(), checksumVector.begin(), checksumVector.end());
        return message;
    }
};

class ChecksumXOR : public Checksum {
public:
    virtual unsigned short calcChecksum(std::string message) {
        unsigned char resultadoXor = 0;
        for (unsigned int i = 0; i < message.size(); i++) {
            resultadoXor ^= message[i];
        }
        return resultadoXor;
    }

    std::string appendChecksum(std::string message, size_t checksumBytes) {
        unsigned short checksum = calcChecksum(message);
        std::string checksumStr(checksumBytes, 0);
        for (unsigned int i = 0; i < checksumBytes; i++) {
            checksumStr[checksumBytes - 1 - i] = (checksum >> (8 * i)) & 0xFF;
        }
        return message + checksumStr;
    }
};

int main() {
    Checksum checksum;
    std::vector<unsigned char> vec = { 'H', 'e', 'l', 'l', 'o' };
    std::vector<unsigned char> resultSum = checksum.appendChecksum(vec, 3);

    ChecksumXOR checksumXor;
    std::string message = "Hello";
    std::string resultXor = checksumXor.appendChecksum(message, 3);

    printf("Mensagem com checksum (SUM): ");
    for (unsigned char byte : resultSum) {
        printf("%d ", byte);
    }
    printf("\n");

    printf("Mensagem com checksum (XOR): ");
    for (unsigned char byte : resultXor) {
        printf("%d ", byte);
    }
    printf("\n");

    return 0;
}

#include <stdio.h>
#include <vector>
#include <string>

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

int main() {
    CustomChecksum customChecksum; // Usa a nova classe CustomChecksum
    std::vector<unsigned char> vec = {'H', 'e', 'l', 'l', 'o'};
    printf("Checksum is %u\n", customChecksum.calcChecksum(vec));
    
    return 0;
}

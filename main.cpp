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
    
    virtual bool doChecksum(std::vector<unsigned char> message, unsigned short checksumValue) {
        return (checksumValue == calcChecksum(message));
    }
};

class CustomChecksumXOR: public Checksum {
public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
        unsigned char resultadoxor = 0;
        for(unsigned int i=0; i<message.size(); i++){
            if(i==0){
                resultadoxor=message[i];
            }else{
                resultadoxor=resultadoxor^message[i];
            } 
                   }
        return resultadoxor;
       }
};

int main() {
    Checksum checksum; // Usa a nova classe CustomChecksum
    std::vector<unsigned char> vec = {'H', 'e', 'l', 'l', 'o'};
    printf("Checksum is %u\n", checksum.calcChecksum(vec));
    
    CustomChecksumXOR Customchecksum; // Usa a nova classe CustomChecksum
    printf("Checksum is %u\n", Customchecksum.calcChecksum(vec));
    return 0;
}

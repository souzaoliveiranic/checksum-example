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
    
    void appendChecksum(std::vector<unsigned char>& message, unsigned short checksum) {
        message.push_back((checksum >> 8) & 0xFF); //Comparativo que vi na net para dividir os bits
        message.push_back(checksum & 0xFF);     //Comparativo que vi na net para dividir os bits
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
    
    //TESTANDO OS VALORES PARA O PRIMEIRO CHECKSUM
    
    unsigned short checksumValue = checksum.calcChecksum(vec1);

    Checksum checksum2;
    checksum2.appendChecksum(vec1, checksumValue);  
    
    printf("Mensagem com checksum no final (questão 2): ");
    for (unsigned char c : vec1) {
        printf("%u ", c);  
    }
    printf("\n");


    return 0;
}

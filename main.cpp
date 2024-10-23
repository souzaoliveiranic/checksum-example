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

    // Novo método para adicionar checksum ao final da mensagem
    virtual void appendChecksum(std::vector<unsigned char>& message, unsigned short checksumValue, unsigned int checksumSize) {
        for (unsigned int i = 0; i < checksumSize; i++) {
            unsigned char byte = (checksumValue >> (8 * (checksumSize - 1 - i))) & 0xFF;
            message.push_back(byte);
        }
    }
    

};


class ChecksumXOR : public Checksum {
    public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
        unsigned char resultadoXor = 0;
        for(unsigned int i = 0; i < message.size(); i++) {
            if (i == 0){
                resultadoXor = message[i];
            }
            else{
                resultadoXor = resultadoXor ^ message[i];
            }

        }
        return resultadoXor;
    }


};




int main() {

    Checksum checksum;
    std::vector<unsigned char> vec = { 'H','e','l','l','o' };

    printf("Checksum (soma) is %u\n", checksum.calcChecksum(vec));


    ChecksumXOR checksumXOR;
    printf("Checksum (XOR) is %u\n", checksumXOR.calcChecksum(vec));
    

    // Adiciona checksum ao final da mensagem
    checksum.appendChecksum(vec, checksum.calcChecksum(vec), 2); // Exemplo: adiciona 2 bytes de checksum

    // Exibe mensagem com checksum anexado
    printf("Mensagem com checksum: ");
    for (unsigned char c : vec) {
        printf("%02X ", c);
    }
    printf("\n");


    return 0;
}





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

// Nova classe que sobrescreve o método de checksum
class MyChecksum : public Checksum {
public:
    unsigned int calcChecksum(std::vector<unsigned char> message) override {
        unsigned int sum = 0;

        // Preencher com 0x00 se o tamanho do pacote for ímpar
        if (message.size() % 2 != 0) {
            message.push_back(0x00);  // Adiciona 0x00 ao final se o tamanho for ímpar
        }

        // Soma de 2 em 2 bytes
        for (size_t i = 0; i < message.size(); i += 2) {
            unsigned short palavra = (message[i] << 8) | message[i + 1];  // Combina dois bytes
            sum += palavra;
        }

        // Retorna os dois bytes menos significativos da soma
        return sum & 0xFFFF;  // Apenas os dois bytes menos significativos
    }
    
    // Sobrescrevendo o método para string como um exemplo, se necessário
    unsigned int calcChecksum(std::string message) override {
        std::vector<unsigned char> byteMessage(message.begin(), message.end());
        return calcChecksum(byteMessage);  // Converte string para vetor de bytes e usa o método
    }
};

int main() {
    MyChecksum checksum;

    // Testando com std::string
    std::string str = "Hello, World!";
    printf("Checksum de '%s' é %u\n", str.c_str(), checksum.calcChecksum(str));

    // Testando com std::vector<unsigned char>
    std::vector<unsigned char> vec = {'H', 'e', 'l', 'l', 'o'};
    printf("Checksum do vetor é %u\n", checksum.calcChecksum(vec));

    return 0;
}

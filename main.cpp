#include <stdio.h>
#include <vector>
#include <string>

class Checksum {
public:
    virtual unsigned int calcChecksum(std::string message) {
        unsigned int sum = 0;
        for (int i = 0; i < message.size(); i++) {
            sum += static_cast<unsigned char>(message[i]);
        }
        return sum;
    }
    
    virtual bool doChecksum(std::string message, unsigned int checksumValue) {
        return (checksumValue == calcChecksum(message));
    }
    
    virtual unsigned int calcChecksum(std::vector<unsigned char> message) {
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

class CustomChecksum : public Checksum {
public:
    // Sobrescreve o método de cálculo do checksum com string
    unsigned int calcChecksum(std::string message) override {
        std::vector<unsigned char> byteVector(message.begin(), message.end());
        return calcChecksum(byteVector);
    }

    // Sobrescreve o método de cálculo do checksum com vetor de bytes
    unsigned int calcChecksum(std::vector<unsigned char> message) override {
        // Se o tamanho do pacote for ímpar, adicionar 0x00 no final
        if (message.size() % 2 != 0) {
            message.push_back(0x00);  // Adiciona 0x00 se o tamanho for ímpar
        }

        unsigned int sum = 0;
        // Itera sobre o vetor somando 2 bytes por vez
        for (size_t i = 0; i < message.size(); i += 2) {
            // Combine os dois bytes adjacentes
            unsigned int word = (message[i] << 8) + message[i + 1]; // Combina dois bytes
            sum += word;
        }

        // Retorna os 2 bytes menos significativos do resultado final
        return sum & 0xFFFF; // Máscara para pegar os 16 bits menos significativos
    }
};

int main() {
    CustomChecksum customChecksum; // Usa a nova classe CustomChecksum
    std::string str = "Hello, World!";
    printf("Checksum of '%s' is %u\n", str.c_str(), customChecksum.calcChecksum(str));
    
    std::vector<unsigned char> vec = {'H', 'e', 'l', 'l', 'o'};
    printf("Checksum is %u\n", customChecksum.calcChecksum(vec));
    
    return 0;
}

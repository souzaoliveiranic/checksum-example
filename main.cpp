#include <stdio.h>
#include <vector>
#include <string>

// Classe base de Checksum
class Checksum {
public:
    // Calcula o checksum somando os valores da mensagem
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
        unsigned int sum = 0;
        for (int i = 0; i < message.size(); i++) {
            sum += message[i];
        }
        return sum;
    }

    // Verifica se o checksum corresponde ao valor dado
    virtual bool doChecksum(std::vector<unsigned char> message, unsigned int checksumValue) {
        return (checksumValue == calcChecksum(message));
    }

    // Adiciona o checksum ao final da mensagem com tamanho fixo de bytes
    void adicionarChecksum(std::vector<unsigned char>& message, int tamanhoBytes) {
        unsigned short checksum = calcChecksum(message);
        std::vector<unsigned char> checksumBytes(tamanhoBytes, 0); // Inicializa com zeros

        // Preenche os bytes do checksum
        for (int i = 0; i < tamanhoBytes; i++) {
            checksumBytes[i] = (checksum >> (8 * (tamanhoBytes - i - 1))) & 0xFF;
        }

        // Adiciona o checksum à mensagem
        message.insert(message.end(), checksumBytes.begin(), checksumBytes.end());
    }
};


class ChecksumXOR : public Checksum {
public:
   
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) override {
        unsigned char resultadoXOR = 0;
        for (unsigned int i = 0; i < message.size(); i++) {
            resultadoXOR ^= message[i];
        }
        return resultadoXOR;
    }
};

int main() {
    Checksum checksum;
    std::vector<unsigned char> vec = { 'H', 'e', 'l', 'l', 'o' };
    printf("Checksum is %u\n", checksum.calcChecksum(vec));
    
    checksum.adicionarChecksum(vec, 3);
    printf("Mensagem com checksum: ");
    for (unsigned char c : vec) {
        printf("%02X ", c); 
    }
    printf("\n");

    return 0;
}

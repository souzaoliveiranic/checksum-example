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

    void adicionar_Checksum(std::vector<unsigned char>& message) {
        unsigned short checksum = calcChecksum(message);
        message.push_back((checksum >> 0) & 0xFF);  
        message.push_back((checksum >> 8) & 0xFF);  
        message.push_back(0);                        
    }
};

class Checksum_XOR : public Checksum {
public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
        unsigned char resultado_XOR = 0;
        for (unsigned int i = 0; i < message.size(); i++) {
            resultado_XOR ^= message[i];  
        }
        return resultado_XOR;
    }
};

int main() {
    std::string str = "Hello, World!";
    std::vector<unsigned char> message(str.begin(), str.end());

    Checksum checksum;
    checksum.adicionar_Checksum(message); 

    Checksum_XOR checksum_XOR;
    checksum_XOR.adicionar_Checksum(message); 

    printf("Mensagem com checksum adicionado: ");
    for (unsigned char byte : message) {
        printf("%c", byte);
    }
    printf("\n");

    std::vector<unsigned char> vec = {'H','e','l','l','o'};
    printf("Checksum (Checksum class) is %hu\n", checksum.calcChecksum(vec));
    printf("Checksum (Checksum_XOR class) is %hu\n", checksum_XOR.calcChecksum(vec));

    return 0;
}

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

class Checksum_XOR : public Checksum {
public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
        unsigned char resultado_XOR = 0;
        for (unsigned int i = 0; i < message.size(); i++) {
            if (i == 0) {
                resultado_XOR = message[i];
            }
            else {
                resultado_XOR = resultado_XOR ^ message[i];  // Ponto e vírgula adicionado aqui
            }
        }
        return resultado_XOR;
    }
};

int main() {

    std::string str = "Hello, World!";
    std::vector<unsigned char> message(str.begin(), str.end());

    Checksum checksum;
    unsigned short checksumValue = checksum.calcChecksum(message);

    Checksum_XOR checksum_XOR;
    unsigned short checksumXORValue = checksum_XOR.calcChecksum(message);
    
    std::vector<unsigned char> vec = {'H','e','l','l','o'};
    printf("Checksum (Checksum class) is %hu\n", checksum.calcChecksum(vec));
    printf("Checksum (Checksum_XOR class) is %hu\n", checksum_XOR.calcChecksum(vec));
    
    return 0;
}

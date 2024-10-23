#include <iostream>
#include <vector>
#include <string>

class Checksum {
public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
        unsigned int sum = 0;
        for (size_t i = 0; i < message.size(); i++) {
            sum += message[i];
        }
        return sum;
    }
    
    virtual bool doChecksum(std::vector<unsigned char> message, unsigned short checksumValue) {
        return (checksumValue == calcChecksum(message));
    }

    // Método para anexar o checksum à mensagem
    virtual void appendChecksum(std::vector<unsigned char>& message, int checksumSize) {
        unsigned short checksum = calcChecksum(message);
        
        // Anexando o checksum aos bytes especificados
        for (int i = 0; i < checksumSize; i++) {
            message.push_back((checksum >> (8 * (checksumSize - 1 - i))) & 0xFF);
        }
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
    std::vector<unsigned char> vec = {'H', 'e', 'l', 'l', 'o'};

    Checksum checksum; // Usa a classe base Checksum
    std::cout << "Checksum (base): " << checksum.calcChecksum(vec) << std::endl;
    
    // Anexando o checksum à mensagem
    checksum.appendChecksum(vec, 3); // Anexando 3 bytes de checksum
    std::cout << "Checksum (base) anexado: ";
    for (int i = vec.size() - 3; i < vec.size(); i++) { // Apenas os últimos 3 bytes
        std::cout << static_cast<int>(vec[i]) << " "; // Imprimindo como inteiro
    }
    std::cout << std::endl;

    CustomChecksumXOR customChecksum; // Usa a classe CustomChecksumXOR
    std::cout << "Checksum (XOR): " << customChecksum.calcChecksum(vec) << std::endl;
    
    // Anexando o checksum à mensagem
    customChecksum.appendChecksum(vec, 3); // Anexando 3 bytes de checksum
    std::cout << "Checksum (XOR) anexado: ";
    for (int i = vec.size() - 3; i < vec.size(); i++) { // Apenas os últimos 3 bytes
        std::cout << static_cast<int>(vec[i]) << " "; // Imprimindo como inteiro
    }
    std::cout << std::endl;


    return 0;
}

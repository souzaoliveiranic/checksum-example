#include <stdio.h>
#include <vector>
#include <string>

class Checksum {
    public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
       unsigned int sum = 0;
       for(int i = 0; i < message.size(); i++) {
          sum += message[i];
       } 
       return sum;
    }
    
    virtual bool doChecksum(std::vector<unsigned char> message, unsigned int checksumValue){
        return (checksumValue == calcChecksum(message));
    }

    virtual std::vector<unsigned char> adicionar_checksum(std::vector<unsigned char> message, unsigned short calcChecksum) {
        message.push_back(calcChecksum);
        return message;
    }
};

class ChecksumXOR: public Checksum {
   public:
   virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
       unsigned short resultadoXor = 0;
       for(unsigned int i = 0; i < message.size(); i++){
         if (i == 0){
            resultadoXor = message[i];
         }
         else {
            resultadoXor = resultadoXor ^ message[i];
         }
       }
       return resultadoXor;
    }
};

int main() {
    
   Checksum checksum;
   std::vector<unsigned char> vec = {'H','e','l','l','o'};
   printf("Checksum is %u\n", checksum.calcChecksum(vec));

   ChecksumXOR checksumXOR;
   printf("Checksum is %u\n", checksumXOR.calcChecksum(vec));

   std::vector<unsigned char> vetor_com_checksum = checksum.adicionar_checksum(vec, checksum.calcChecksum(vec));
    printf("Message with sum checksum: ");
    for (int i = 0; i < vetor_com_checksum.size(); i++) {
        printf("%c", vetor_com_checksum[i]);
    }
   return 0;
}
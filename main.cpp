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
};

class Checksum22 : public Checksum{
   public:
      virtual unsigned int calcChecksum22(std::vector<unsigned char> message) {
         if(message.size()%2 != 0)
            message.push_back(0x00);
         unsigned int sum = 0;
         for(int i = 0; i < message.size(); i+2){
             sum += message[i];
             sum += message[
         } 
         return sum;
      }

int main() {

    Checksum checksum;
    std::vector<unsigned char> vec = { 'H','e','l','l','o' };
    printf("Checksum is %u\n", checksum.calcChecksum(vec));
    return 0;

}


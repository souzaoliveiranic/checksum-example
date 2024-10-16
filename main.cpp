#include <stdio.h>
#include <vector>
#include <string>

class Checksum {
    public:
    virtual unsigned int calcChecksum(std::string message) {
       unsigned int sum = 0;
       for(int i = 0; i < message.size(); i++) {
          sum += message[i];
       } 
       return sum;
    }
    
    virtual bool doChecksum(std::string message, unsigned int checksumValue){
        return (checksumValue == calcChecksum(message));
    }
    
    virtual unsigned int calcChecksum(std::vector<unsigned char> message) {
       unsigned int sum = 0;
       for(int i = 0; i < message.size(); i++) {
          sum += message[i];
       } 
       return sum;
    }
    
    virtual bool doChecksum(std::vector<unsigned char> message, unsigned int checksumValue){
        return (checksumValue == calcChecksum(message));
    }
};

int main() {
    
    Checksum checksum;
   std::string str = "Hello, World!";
   printf("Checksum of '%s' is %u\n", str.c_str(), checksum.calcChecksum(str));
   
   std::vector<unsigned char> vec = {'H','e','l','l','o'};
    printf("Checksum is %u\n", checksum.calcChecksum(vec));
   return 0;
}

///Rabelo irá commitar.
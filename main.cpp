#include <stdio.h>
#include <vector>
#include <string>

class Checksum {
    public:
    static unsigned int calcChecksum(std::string message) {
       unsigned int sum = 0;
       for(int i = 0; i < message.size(); i++) {
          sum += message[i];
       } 
       return sum;
    }
    
    static bool doChecksum(std::string message, unsigned int checksumValue){
        return (checksumValue == calcChecksum(message));
    }
    
    static unsigned int calcChecksum(std::vector<unsigned char> message) {
       unsigned int sum = 0;
       for(int i = 0; i < message.size(); i++) {
          sum += message[i];
       } 
       return sum;
    }
    
    static bool doChecksum(std::vector<unsigned char> message, unsigned int checksumValue){
        return (checksumValue == calcChecksum(message));
    }
};

int main() {
    
   std::string str = "Hello, World!";
   printf("Checksum of '%s' is %u\n", str.c_str(), Checksum::calcChecksum(str));
   
   std::vector<unsigned char> vec = {'H','e','l','l','o'};
    printf("Checksum is %u\n", Checksum::calcChecksum(vec));
   return 0;
}
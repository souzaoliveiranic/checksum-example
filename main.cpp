#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

class Checksum {
    public:
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

class ModChecksum : public Checksum{
   public:
   unsigned int calcChecksum(string message) {
      
   }
};

int main() {  
   ModChecksum teste;
   Checksum checksum;

   std::vector<unsigned char> vec = {'H','e','l','l','o'};
    printf("Checksum is %u\n", checksum.calcChecksum(vec));
    
   return 0;    
}


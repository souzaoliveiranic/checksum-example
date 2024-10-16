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

class Checksumnova : public Checksum {
   public:
      virtual unsigned int novaChecksum(std::string message) {
      if (message.size() % 2 != 0) {
         message += '\0';
      }

      
      unsigned int sum = 0;
      
      for (size_t i = 0; i < message.size(); i += 2) {
         unsigned short word = (message[i] << 4) + (message[i + 1] & 0x0F);
         sum += word;
      }
      return sum & 0xFFFF; 
    }
   }

int main() {
    
   Checksum checksum;
   Checksumnova checksumnova;
   std::string str = "Hello, World!";
   printf("Checksum of '%s' is %u\n", str.c_str(), checksum.calcChecksum(str));
   printf("Checksum of '%s' is %u\n", str.c_str(), checksumnova.novaChecksum(str));  


   std::vector<unsigned char> vec = {'H','e','l','l','o'};
   printf("Checksum is %u\n", checksum.calcChecksum(vec));
   printf("Checksum is %u\n", checksumnova.novaChecksum("Hello"));
   return 0;
}
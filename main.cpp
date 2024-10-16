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
   std::string str = "Hello, World!";
   printf("Checksum of '%s' is %u\n", str.c_str(), checksum.calcChecksum(str));
   
   std::vector<unsigned char> vec = {'H','e','l','l','o'};
    printf("Checksum is %u\n", checksum.calcChecksum(vec));
   return 0;
}
#include <stdio.h>
#include <vector>
#include <string>

class Checksum {
public:
   virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
      unsigned short sum = 0;
         for(unsigned int i = 0; i < message.size(); i++) {
            sum += message[i];
         } 
      return sum;
      
      }

   virtual unsigned short addChecksum(std::vector<unsigned char>& message, unsigned short calcChecksum()) {
      unsigned short valorChecksum = calcChecksum();
      message.push_back(static_cast<unsigned short>(valorChecksum)); 
      return message;
   }
         
   virtual bool doChecksum(std::vector<unsigned char> message, unsigned int checksumValue){
      return (checksumValue == calcChecksum(message));
   }  
};


class ChecksumXOR : public Checksum {
public:
   virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
      unsigned char resultadoXor = 0;
         for(unsigned int i = 0; i < message.size(); i++) {
            if(i == 0) {
               resultadoXor = message[i];
            } else {
            resultadoXor = resultadoXor ^ message[i];
            }
         } 
      return resultadoXor; 
      }

    virtual unsigned short addChecksumXOR(std::vector<unsigned char>& message, unsigned short calcChecksum()) {
      unsigned short valorChecksumXor = calcChecksum();
      message.push_back(static_cast<unsigned short>(valorChecksumXor));
      return message;
   }         

};

int main() {
    
   Checksum checksum;
   std::vector<unsigned char> vec = {'H','e','l','l','o'};
   printf("Checksum is %u\n", checksum.calcChecksum(vec));

   ChecksumXOR checksumXOR;
   printf("ChecksumXOR is %u\n", checksumXOR.calcChecksum(vec));

   checksum.addChecksum(vec, checksum.calcChecksum(vec));
   printf("Message with Checksum: ");
   for (unsigned short c : vec) {
       printf("%02X ", c);
   }
   printf("\n");

   checksumXOR.addChecksum(vec, checksumXOR.calcChecksum(vec));
   printf("Message with ChecksumXOR: ");
   for (unsigned short c : vec) {
       printf("%02X ", c);
   }
   printf("\n");

   return 0;
}
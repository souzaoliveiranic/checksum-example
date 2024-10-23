#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

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

   void addChecksum(vector<unsigned char>& message, unsigned short checksum){
      unsigned short checksumValue = checksum;
      message.push_back(checksumValue);
   }
};

class XorChecksum : public Checksum{
   public:
    virtual unsigned short calcChecksum(std::vector<unsigned char> message) {
      unsigned char resultadoXor = 0;
      for (unsigned int i = 0; i < message.size(); i++)
      {
      if(i==0) {
         resultadoXor = message[i];
      } else {
         resultadoXor = resultadoXor^message[i];
      }
      }
      
       return resultadoXor;
    }
   };

int main() {  
   XorChecksum teste;
   Checksum checksum;

   std::vector<unsigned char> vec = {'H','e','l','l','o'};
   printf("Checksum is %u\n", checksum.calcChecksum(vec));

   printf("ChecksumXOR is %u\n", teste.calcChecksum(vec));
   printf("%u\n", vec.back());

   teste.addChecksum(vec, teste.calcChecksum(vec));
   printf("%u", vec.back());
   return 0;    
}


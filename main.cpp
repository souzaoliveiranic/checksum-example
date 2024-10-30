#include <stdio.h>
#include <vector>
#include <string>
#include <bitset>

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

class Packer{
   public:
   vector<unsigned char> addHead(vector<unsigned char> data_, int id){
   
   vector<unsigned char> data = data_;
   
   if(id>15||id<0){
      printf("Id invalido!");
      data.clear();
      return data;
   }
   if(data.size()>16){
      printf("Tamanho invalido (>16 bytes)");
      data.clear();
      return data;
   }
   unsigned char h = '\0';
  
      h = h | ((id & 0x0F)<<4);
      h = h | (data.size() & 0x0F);
   
   data.insert(data.begin(), h);
   return data;
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
   printf("%u\n", vec.back());

   Packer teste2;
   vec = teste2.addHead(vec, 3);
   printf("Vec com header: %u", vec[0]);
   return 0;
}


#include <stdio.h>
#include <vector>
#include <string>

class Checksum
{
public:
   virtual unsigned short calcChecksum(std::vector<unsigned char> message)
   {
      unsigned int sum = 0;
      for (int i = 0; i < message.size(); i++)
      {
         sum += message[i];
      }
      return sum;
   }

   virtual bool doChecksum(std::vector<unsigned char> message, unsigned int checksumValue)
   {
      return (checksumValue == calcChecksum(message));
   }
};

class ChecksumXOR : public Checksum
{
public:
   // Sobrescreve o método de cálculo do checksum usando XOR
   unsigned short calcChecksum(std::vector<unsigned char> message) override
   {
      unsigned char resultadoXOR = 0;
      for (unsigned int i = 0; i < message.size(); i++)
      {
         if (i == 0)
         {
            resultadoXOR = message[0];
         }
         else
         {
            resultadoXOR = resultadoXOR ^ message[i];
         }
      }
      return resultadoXOR;
   }
};

int main()
{
   Checksum checksum;

   std::vector<unsigned char> vec = {'H', 'E', 'L', 'L', 'O'};
   printf("Checksum (soma) is %u\n", checksum.calcChecksum(vec));

   ChecksumXOR checksumXOR;

   printf("Checksum (XOR) is %u\n", checksumXOR.calcChecksum(vec));

   return 0;
}

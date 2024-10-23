#include <stdio.h>
#include <vector>
#include <string>
#include <iostream> // Para usar cout
#include <sstream>  // Para converter números para string

class Checksum
{
public:
   // Calcula o checksum somando os bytes da mensagem
   virtual unsigned short calcChecksum(const std::vector<unsigned char> &message)
   {
      unsigned int sum = 0;
      for (int i = 0; i < message.size(); i++)
      {
         sum += message[i];
      }
      return sum;
   }

   // Adiciona o checksum como string decimal (usando os dois bytes em decimal)
   virtual std::string appendChecksumAsDecimal(const std::vector<unsigned char> &message)
   {
      unsigned short checksumValue = calcChecksum(message);
      std::string newMessage(message.begin(), message.end()); // Converte a mensagem para string

      // Extrai os dois bytes do checksum
      unsigned char LSB = checksumValue & 0xFF;        // Byte menos significativo
      unsigned char MSB = (checksumValue >> 8) & 0xFF; // Byte mais significativo

      // Concatena os dois valores em decimal ao final da mensagem
      newMessage += std::to_string(MSB); // Adiciona o byte mais significativo (em decimal)
      newMessage += std::to_string(LSB); // Adiciona o byte menos significativo (em decimal)

      return newMessage;
   }
};

class ChecksumXOR : public Checksum
{
public:
   // Sobrescreve o método de cálculo do checksum usando XOR
   unsigned short calcChecksum(const std::vector<unsigned char> &message) override
   {
      unsigned char resultadoXOR = 0;
      for (unsigned int i = 0; i < message.size(); i++)
      {
         resultadoXOR ^= message[i];
      }
      return resultadoXOR;
   }

   // Adiciona o checksum XOR como decimal ao final da mensagem
   std::string appendChecksumAsDecimal(const std::vector<unsigned char> &message) override
   {
      unsigned short checksumValue = calcChecksum(message);
      std::string newMessage(message.begin(), message.end()); // Converte a mensagem para string

      // Concatena o valor do checksum XOR em decimal ao final da mensagem
      newMessage += std::to_string(checksumValue);

      return newMessage;
   }
};

int main()
{
   Checksum checksum;
   ChecksumXOR checksumXOR;

   std::vector<unsigned char> vec = {'H', 'e', 'l', 'l', 'o'};

   // Calcula e exibe o checksum de soma
   printf("Checksum (soma) is %u\n", checksum.calcChecksum(vec));
   std::string messageWithChecksum = checksum.appendChecksumAsDecimal(vec);
   std::cout << "Mensagem com checksum (soma): " << messageWithChecksum << std::endl;

   // Calcula e exibe o checksum XOR
   printf("Checksum (XOR) is %u\n", checksumXOR.calcChecksum(vec));
   std::string messageWithChecksumXOR = checksumXOR.appendChecksumAsDecimal(vec);
   std::cout << "Mensagem com checksum (XOR): " << messageWithChecksumXOR << std::endl;

   return 0;
}

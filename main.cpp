#include <stdio.h>
#include <vector>
#include <string>

class Checksum {
    public:
    virtual unsigned short calcChecksum(std::string message) {
       unsigned short sum = 0;
       for(unsigned int i = 0; i < message.size(); i++) {
          sum += message[i];
       } 
       return sum;
    }
    
    virtual bool doChecksum(std::string message, unsigned short checksumValue){
        return (checksumValue == calcChecksum(message));
    }
};

int main() {
    
    Checksum checksum;
	std::string str = "Hello, World!";
	printf("Checksum of '%s' is %u\n", str.c_str(), checksum.calcChecksum(str));
   
	return 0;
}


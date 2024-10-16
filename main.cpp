#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

class Checksum {
    public:
    virtual unsigned int calcChecksum(string message) {
       unsigned int sum = 0;
       for(int i = 0; i < message.size(); i++) {
          sum += message[i];
       } 
       return sum;
    }
    
    virtual bool doChecksum(string message, unsigned int checksumValue){
        return (checksumValue == calcChecksum(message));
    }
    
    virtual unsigned int calcChecksum(vector<unsigned char> message) {
       unsigned int sum = 0;
       for(int i = 0; i < message.size(); i++) {
          sum += message[i];
       } 
       return sum;
    }
    
    virtual bool doChecksum(vector<unsigned char> message, unsigned int checksumValue){
        return (checksumValue == calcChecksum(message));
    }
};

int main() {

    Checksum checksum;
    string str = "Hello, World!";
    printf("Checksum of '%s' is %u\n", str.c_str(), checksum.calcChecksum(str));
   
    vector<unsigned char> vec = {'H','e','l','l','o'};
    printf("Checksum is %u\n", checksum.calcChecksum(vec));
    return 0;

}

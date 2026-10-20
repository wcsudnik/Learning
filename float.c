#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIGN_BIT 0x80000000
#define INFINITY_POS 0b01111111100000000000000000000000
#define INFINITY_NEG 0b11111111100000000000000000000000
#define EXPONENT 0x7F800000
#define MANTISSA 0x007FFFFF

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 

union FloatBits{
    float f;
    u_int32_t u;
};  

int bFlag(char* input){
    int bits = 0;
    int i = 0;
    while ((input[i]) != '\0'){
        bits = bits << 1;
        if ((input[i]) == '1') {
            bits = bits | 1;
        }
        i++;
    }
    return bits;
}

int getExponent(u_int32_t num) {
    u_int32_t mod = (num & EXPONENT) >> 23;
    return (int)mod - 127;
}


int main(int argc, char* argv[]){
    
    union FloatBits fb;
    
    if ((argc > 1) && argv[1][1] == 'f'){
       fb.f = strtof(argv[2], NULL);
    }
    else if ((argc > 1) && argv[1][1] == 'b'){
        fb.u = bFlag(argv[2]);
    }
    
    printf("Binary representation: "BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(fb.u>>24), BYTE_TO_BINARY(fb.u>>16), BYTE_TO_BINARY(fb.u>>8), BYTE_TO_BINARY(fb.u));;
    printf("Sign: %i\n", (fb.u & SIGN_BIT) >> 31);
    printf("Exponent: %i\n", getExponent(fb.u));
    printf("Mantissa: %.7g\n", 1.0 + ((double)(fb.u & MANTISSA) / (1 << 23)));
    printf("Value: %.7g\n", fb.f);
    
}

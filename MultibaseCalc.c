/*
Multibase RPN Calculator that accepts 20 command line args in either decimal, hexadecimal, or binary.
Ops are "add", "sub", "mult", "div"
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX 20

long binConverter(char* binary);
long decimalConverter(char* input);
long hexConverter(char* input);

int main(int argc, char* argv[]){
    long stack[20];
    int top = 0;
    long val;
    char* end;
    long result;

        
        for (int j=1;j<argc;j++){
            if (strncmp(argv[j], "add", 3) == 0){ 
                printf("adding %ld and %ld\n", stack[top], stack[top-1]);
                result = stack[top] + stack[top - 1];
                stack[top] = result;
            }
            else if (strncmp(argv[j], "sub", 3)==0){ 
                result = stack[top] - stack[top - 1];
                stack[top] = -1 * result;
            }
            else if (strncmp(argv[j], "mult", 3)==0){ 
                result = stack[top] * stack[top - 1];
                stack[top] = result;
            }
            else if (strncmp(argv[j], "div", 3) ==0){ 
                result = (stack[top]) / (stack[top - 1]);
                stack[top] = result;
            }
            else if (strncmp(argv[j], "0b", 2)==0){ 
                stack[++top] = binConverter(argv[j]);
            }
            else if (strncmp(argv[j], "0x", 2)==0){ 
                stack[++top] = hexConverter(argv[j]);
            }
            else {
                stack[++top] = decimalConverter(argv[j]);
            }
        }
        
    printf("%ld", stack[top]);
    return 0;
}

long hexConverter(char* input){
    int length = 0;
    while (input[length] != '\0'){
        length++;
    }
    long decimalnumber, i;
    int cnt;
    int digit;
    cnt = 0;
    decimalnumber = 0;
    for (i = (length - 1); i >= 2; i--) {
        switch (input[i]) {
        case 'A':
            digit = 10;
            break;
        case 'B':
            digit = 11;
            break;
        case 'C':
            digit = 12;
            break;
        case 'D':
            digit = 13;
            break;
        case 'E':
            digit = 14;
            break;
        case 'F':
            digit = 15;
            break;
        case 'a':
            digit = 10;
            break;
        case 'b':
            digit = 11;
            break;
        case 'c':
            digit = 12;
            break;
        case 'd':
            digit = 13;
            break;
        case 'e':
            digit = 14;
            break;
        case 'f':
            digit = 15;
            break;
        default:
            digit = input[i] - 0x30;
        }
        decimalnumber = decimalnumber + (digit)*pow((double)16, (double)cnt);
        cnt++;
    }
    return decimalnumber;
}

long binConverter(char* binary){
    long dec = 0;
    int length = 0;
    while (binary[length] != '\0'){
        length++;
    }
    int base = 1;
    for (int i = length - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            dec += base;
        }
        base = base * 2;
    }
    return dec;
}

long decimalConverter(char* str){
    
long num = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 48 && str[i] <= 57) {
            num = num * 10 + (str[i] - 48);
        }
        else {
            break;
        }
    }

    return num;
}

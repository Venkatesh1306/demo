#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define INPUT_SIZE 12


#define testing

#define BYTE unsigned char
#define WORD unsigned short

void in_func(BYTE input[]); 
void res_func(WORD output[],WORD Reg[]);

typedef union {
    WORD Val;
    BYTE v[2];
} WORD_VAL;



#ifdef testing
void test(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
#endif



void in_func(BYTE input[]);
void res_func(WORD output[],WORD Reg[]);
void test(const char *format, ...);

BYTE Reg[100];

typedef struct {
    WORD_VAL transaction_identifier;
    WORD_VAL protocol_identifier;
    WORD_VAL length;
    BYTE unit_identifier;
    BYTE function_code;
    WORD_VAL start_address;
    WORD_VAL address_length;
} Modbus;

Modbus parse;

void in_func(BYTE input[]) {
    parse.transaction_identifier.v[1]   = input[0];
    parse.transaction_identifier.v[0]   = input[1];
    parse.protocol_identifier.v[1]      = input[2];
    parse.protocol_identifier.v[0]      = input[3];
    parse.length.v[1]                   = input[4];
    parse.length.v[0]                   = input[5];
    parse.unit_identifier               = input[6];
    parse.function_code                 = input[7];
    parse.start_address.v[1]            = input[8];
    parse.start_address.v[0]            = input[9];
    parse.address_length.v[1]           = input[10];
    parse.address_length.v[0]           = input[11]; 

#ifdef testing
    test("Transaction Identifier: %04X\n", parse.transaction_identifier.Val);
    test("Protocol Identifier: %04X\n", parse.protocol_identifier.Val);
    test("Length: %04X\n", parse.length.Val);
    test("Unit Identifier: %02X\n", parse.unit_identifier);
    test("Function Code: %02X\n", parse.function_code);
    test("Start Address: %04X\n", parse.start_address.Val);
    test("Address Length: %04X\n", parse.address_length.Val);
#endif
}
void res_func(WORD output[],WORD Reg[]) {
    output[0] = parse.transaction_identifier.v[1];
    output[1] = parse.transaction_identifier.v[0];
    output[2] = parse.protocol_identifier.v[1];
    output[3] = parse.protocol_identifier.v[0];
    output[4] = parse.length.v[1];
    output[5] = parse.length.v[0] - 2;
    output[6] = parse.unit_identifier;
    output[7] = parse.function_code;
    
    WORD a = parse.start_address.Val;
    int b = parse.address_length.Val;
    int i;
    BYTE byt_cnt = (BYTE)(b*2);

    output[8] = byt_cnt;

    for(i = 0; i < b; i++) {
        output[i + 9] = Reg[a + i - 1];
    }

    // Printing the output in string format
    test("Output string: ");
    for(int i = 0; i <= 8 ; i++) {
        test("%02X ", output[i]);
    }
    for(int i = 9; i < 9 + parse.address_length.Val; i++) {
        test("%04X ", output[i]);
    }
    test("\n");
}

int main() {
    BYTE input[100] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x06, 0x00, 0x04, 0x00, 0x03};
    WORD Reg[100]   = {0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e};
    WORD output[100]; // Assuming output array size is 100
    
   
    in_func(input);
    res_func(output,Reg);

    
    return 0;
}

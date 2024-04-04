#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define INPUT_SIZE 12



#define BYTE unsigned char
#define WORD unsigned short

void test(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

typedef union {
    WORD Val;
    BYTE v[2];
} WORD_VAL;

void in_func(BYTE input[]); // Prototype with input[] as an argument
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

void in_func(BYTE input[]) { // Accept input[] as an argument
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

    test("Transaction Identifier: %04X\n", parse.transaction_identifier.Val);
    test("Protocol Identifier: %04X\n", parse.protocol_identifier.Val);
    test("Length: %04X\n", parse.length.Val);
    test("Unit Identifier: %02X\n", parse.unit_identifier);
    test("Function Code: %02X\n", parse.function_code);
    test("Start Address: %04X\n", parse.start_address.Val);
    test("Address Length: %04X\n", parse.address_length.Val);
}

int main() {
    BYTE input[100] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x00, 0x06, 0x00, 0x02, 0x00, 0x03};

    in_func(input); // Pass input[] to the function
    return 0;
}

#include <stdio.h>
#include <string.h>

typedef struct {
    unsigned short transaction_identifier;
    unsigned short protocol_identifier;
    unsigned short length;
    unsigned char unit_identifier;
    unsigned char function_code;
    unsigned short start_address; 
    unsigned short address_length;
} ModbusTCP_Packet;

void parse_Modbus_TCP_Packet(const char* input, ModbusTCP_Packet* packet) {
    sscanf(input, "%04hx%04hx%04hx%02hhx%02hhx%04hx%04hx",  &packet->transaction_identifier,
                                                            &packet->protocol_identifier,
                                                            &packet->length,
                                                            &packet->unit_identifier,
                                                            &packet->function_code,
                                                            &packet->start_address,
                                                            &packet->address_length);
}

void format_Modbus_TCP_Packet(const ModbusTCP_Packet* packet, unsigned short* hex_values, int num_values, char* output) {
    sprintf(output, "%04X%04X%04X%02X%02X", packet->transaction_identifier,
                                            packet->protocol_identifier,
                                            packet->length,
                                            packet->unit_identifier,
                                            packet->function_code);
    
   for (int i = 0; i < num_values; i++) {
        unsigned char high_byte = hex_values[i] / 256; // Divide by 256 to get the high byte
        unsigned char low_byte = hex_values[i] % 256; // Modulus 256 to get the low byte
        sprintf(output + strlen(output), "%02X%02X", high_byte, low_byte); // Append high and low bytes
    }
}

int main() {
    char input[100];
    ModbusTCP_Packet packet;
    unsigned short value[100] = {0x0304, 0x0567, 0x0765, 0x0565, 0x0701, 0x6633, 0x5533, 0x755, 0x99, 0x5488, 0x89, 0x909, 0x659, 0x7665}; // Array of hexadecimal values
    unsigned short hex_val[100];
    printf("Enter Modbus TCP packet (in hexadecimal format, without spaces):\n");
    fgets(input, sizeof(input), stdin); // Use fgets to safely read input

    parse_Modbus_TCP_Packet(input, &packet);

    if (strlen(input) >= 24) {
        printf("Transaction Identifier: %04X\n", packet.transaction_identifier);
        printf("Protocol Identifier: %04X\n", packet.protocol_identifier);
        printf("Length: %04X\n", packet.length);
        printf("Unit Identifier: %02X\n", packet.unit_identifier);
        printf("Function Code: %02X\n", packet.function_code);
        printf("Start address: %04X\n", packet.start_address);
        printf("Length Address: %04X\n", packet.address_length);

        unsigned short a = packet.start_address;
        int b = packet.address_length;
        int i;

        for(i = 0; i < b; i++) {
            hex_val[i] = value[a + i];
            printf("%04X\n", value[a + i]);
        }

        char output[100];
        format_Modbus_TCP_Packet(&packet, hex_val, b, output);

        printf("Modbus TCP packet in hexadecimal format: %s\n", output);
    } else {
        printf("Failed to parse Modbus TCP packet. Input string is too short.\n");
    }

    return 0;
}

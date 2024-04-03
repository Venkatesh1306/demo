#include <stdio.h>
#include <string.h>

// Structure to store Modbus TCP packet components
typedef struct {
    unsigned short transaction_identifier;
    unsigned short protocol_identifier;
    unsigned short length;
    unsigned char unit_identifier;
    unsigned char function_code;
    unsigned char data_payload[256]; // Adjust the size as needed
} ModbusTCP_Packet;

// Function to parse Modbus TCP packet from input string
void parse_Modbus_TCP_Packet(const char* input, ModbusTCP_Packet* packet) {
    // Parse transaction identifier (bytes 0 and 1)
    sscanf(input, "%04hx", &packet->transaction_identifier);

    // Parse protocol identifier (bytes 2 and 3)
    sscanf(input + 4, "%04hx", &packet->protocol_identifier);

    // Parse length (bytes 4 and 5)
    sscanf(input + 8, "%04hx", &packet->length);

    // Parse unit identifier (byte 6)
    sscanf(input + 12, "%02hhx", &packet->unit_identifier);

    // Parse function code (byte 7)
    sscanf(input + 14, "%02hhx", &packet->function_code);

    // Parse data payload (bytes 8 onwards)
    sscanf(input + 16, "%s", packet->data_payload);
}

int main() {
    char input[100]; // Assuming a maximum input length of 100 characters
    ModbusTCP_Packet packet;

    // Prompt the user for input
    printf("Enter Modbus TCP packet (in hexadecimal format, without spaces):\n");
    scanf("%s", input);

    // Parse the Modbus TCP packet

    parse_Modbus_TCP_Packet(input, &packet);
if (strlen(input) > 12){
    // Display the parsed components
    printf("Transaction Identifier: %04X\n", packet.transaction_identifier);
    printf("Protocol Identifier: %04X\n", packet.protocol_identifier);
    printf("Length: %04X\n", packet.length);
    printf("Unit Identifier: %02X\n", packet.unit_identifier);
    printf("Function Code: %02X\n", packet.function_code);
    printf("Data Payload: %s\n", packet.data_payload);
}
else {
        printf("Failed to parse Modbus TCP packet. Input string is too short.\n");
       
    }
    return 0;
}

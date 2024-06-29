#include "keyboard.h"
#include "io.h"
#include "vga.h"
#include <stddef.h> // for NULL definition

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC_EOI 0x20

static char keymap[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0,
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9',
    '-', '4', '5', '6', '+', '1', '2', '3', '0', '.',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0
};

static char input_buffer[256]; // Buffer to hold user input
static int input_index = 0;    // Index to track position in input_buffer

void keyboard_handler(void) {
    uint8_t status;
    char keycode;

    // Write end of interrupt (EOI) to the PICs
    outb(PIC1_COMMAND, PIC_EOI);

    status = inb(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        keycode = inb(KEYBOARD_DATA_PORT);
        if (keycode >= 0) {
            char c = keymap[(unsigned char)keycode];

            // Handle special keys
            if (c == '\n') {
                input_buffer[input_index] = '\0'; // Null-terminate the string
                input_index = 0; // Reset index for next input
            } else {
                input_buffer[input_index++] = c; // Add character to buffer
            }
        }
    }
}

void keyboard_init(void) {
    outb(0x21, 0xFD);
}

char* get_input(void) {
    for (int i = 0; i < 256; ++i) {
        input_buffer[i] = '\0';
    }
    input_index = 0;

    while (1) { 

        if (input_index > 0 && input_buffer[input_index - 1] == '\0') {
            char *result = (char*)malloc(input_index * sizeof(char));
            if (result == NULL) {
                return NULL;
            }

            strncpy(result, input_buffer, input_index - 1);
            result[input_index - 1] = '\0';
            return result;
        }
    }
}

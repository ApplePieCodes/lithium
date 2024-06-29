#include "keyboard.h"
#include "io.h"
#include "vga.h"

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

void keyboard_handler(void) {
    uint8_t status;
    char keycode;

    outb(PIC1_COMMAND, PIC_EOI);

    status = inb(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        keycode = inb(KEYBOARD_DATA_PORT);
        if (keycode >= 0) {
            char c = keymap[(unsigned char)keycode];
            printChar(0, 0, c, 15);
        }
    }
}

void keyboard_init(void) {
    outb(0x21, 0xFD);
}

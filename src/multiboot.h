#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#define MULTIBOOT2_MAGIC 0xE85250D6

// Define the multiboot_header structure
struct multiboot_header {
    unsigned int magic;
    unsigned int architecture;
    unsigned int header_length;
    unsigned int checksum;
} __attribute__((packed));

// Define the actual instance of multiboot_header
__attribute__((section(".multiboot"))) struct multiboot_header multiboot_header = {
    .magic = MULTIBOOT2_MAGIC,
    .architecture = 0,   // Specify the architecture here, 0 for x86
    .header_length = sizeof(struct multiboot_header),
    .checksum = -(MULTIBOOT2_MAGIC + 0 + sizeof(struct multiboot_header))
};

#endif

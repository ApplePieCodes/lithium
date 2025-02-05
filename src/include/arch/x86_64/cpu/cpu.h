#pragma once

/*
    The Lithium Kernel
    Redistrobution without this header is strictly prohibited. If modifications are made, add your own attribution below.
    @file arch/x86_64/cpu/cpu.h
    @author Liam Greenway
*/

#include <stdint.h>

/// @brief Output one byte to a port
/// @param port Port to output to
/// @param value Byte to output
void outb(uint16_t port, uint8_t value);

/// @brief Output one word to a port
/// @param port Port to output to
/// @param value Word to output
void outw(uint16_t port, uint16_t value);

/// @brief Output one long word to a port
/// @param port Port to output to
/// @param value Long word to output
void outd(uint16_t port, uint32_t value);

/// @brief Read one byte from a port
/// @param port Port to read from
/// @return Byte read from port
uint8_t inb(uint16_t port);

/// @brief Read one word from a port
/// @param port Port to read from
/// @return Word read from port
uint16_t inw(uint16_t port);

/// @brief Read one long word from a port
/// @param port Port to read from
/// @return Long word read from port
uint32_t ind(uint16_t port);

static inline void io_wait(void) {
    outb(0x80, 0);
}
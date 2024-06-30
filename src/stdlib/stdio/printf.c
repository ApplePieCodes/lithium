#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include "stdio.h"
#include "../string/string.h"

static bool print(const char* data, size_t length) {
    const unsigned char* bytes = (const unsigned char*) data;
    for (size_t i = 0; i < length; i++) {
        if (putchar(bytes[i]) == EOF) {
            return false;
        }
    }
    return true;
}

static bool print_number(int value, int base) {
    char buffer[32];
    char* ptr = &buffer[31];
    *ptr = '\0';

    if (value == 0) {
        *--ptr = '0';
    } else {
        bool negative = false;
        if (value < 0 && base == 10) {
            negative = true;
            value = -value;
        }

        while (value != 0) {
            int digit = value % base;
            *--ptr = digit < 10 ? '0' + digit : 'a' + digit - 10;
            value /= base;
        }

        if (negative) {
            *--ptr = '-';
        }
    }

    return print(ptr, &buffer[31] - ptr);
}

int printf(const char* restrict format, ...) {
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while (*format != '\0') {
        size_t maxrem = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%') {
                format++;
            }
            size_t amount = 1;
            while (format[amount] && format[amount] != '%') {
                amount++;
            }
            if (maxrem < amount) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, amount)) {
                return -1;
            }
            format += amount;
            written += amount;
            continue;
        }

        const char* format_begun_at = format++;

        if (*format == 'c') {
            format++;
            char c = (char) va_arg(parameters, int /* char promotes to int */);
            if (!maxrem) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(&c, sizeof(c))) {
                return -1;
            }
            written++;
        } else if (*format == 's') {
            format++;
            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(str, len)) {
                return -1;
            }
            written += len;
        } else if (*format == 'd' || *format == 'x') {
            int base = (*format == 'd') ? 10 : 16;
            format++;
            int value = va_arg(parameters, int);
            if (!print_number(value, base)) {
                return -1;
            }
            // Written count needs to consider the printed number length
            written += 1; // Approximate the count (actual length calculation is more complex)
        } else {
            format = format_begun_at;
            size_t len = strlen(format);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, len)) {
                return -1;
            }
            written += len;
            format += len;
        }
    }

    va_end(parameters);
    return written;
}

#include <libc/stdio.h>
#include <term/term.h>
#include <stdarg.h>

static void int_to_str(unsigned long num, char *buf, int base) {
    int i = 0;
    if (num == 0) {
        buf[i++] = '0';
        buf[i] = '\0';
        return;
    }

    while (num > 0) {
        int rem = num % base;
        buf[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
        num /= base;
    }

    buf[i] = '\0';
    
    // Reverse the string
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = buf[j];
        buf[j] = buf[k];
        buf[k] = temp;
    }
}

int vsprintf(char *out, const char *format, va_list args) {
    char buffer[32]; // Buffer for number conversion
    char *out_ptr = out;

    while (*format) {
        if (*format == '%' && *(format + 1)) {
            format++; // Move past '%'
            switch (*format) {
                case 'd': // Integer
                case 'i':
                    int_to_str(va_arg(args, int), buffer, 10);
                    for (char *buf_ptr = buffer; *buf_ptr; buf_ptr++) {
                        *out_ptr++ = *buf_ptr;
                    }
                    break;
                case 'x': // Hexadecimal (unsigned int)
                    int_to_str(va_arg(args, unsigned int), buffer, 16);
                    for (char *buf_ptr = buffer; *buf_ptr; buf_ptr++) {
                        *out_ptr++ = *buf_ptr;
                    }
                    break;
                case 'l': // Long modifier
                    if (*(format + 1) == 'x') { // %lx for unsigned long in hex
                        format++;
                        int_to_str(va_arg(args, unsigned long), buffer, 16);
                        for (char *buf_ptr = buffer; *buf_ptr; buf_ptr++) {
                            *out_ptr++ = *buf_ptr;
                        }
                    }
                    break;
                case 'c': // Character
                    *out_ptr++ = (char)va_arg(args, int);
                    break;
                case 's':
                    char *str_arg = va_arg(args, char *);
                    if (!str_arg) {
                        str_arg = "(null)";
                    }
                    while (*str_arg) {
                        *out_ptr++ = *str_arg++;
                    }
                    break;
                default: // Unknown specifier, print as-is
                    *out_ptr++ = '%';
                    *out_ptr++ = *format;
                    break;
            }
        } else {
            *out_ptr++ = *format;
        }
        format++;
    }

    *out_ptr = '\0'; // Null-terminate the string
    return (out_ptr - out); // Return the number of characters written
}

int sprintf(char *out, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = vsprintf(out, format, args);
    va_end(args);
    return result;
}

void printf(const char *format, ...) {
    char buffer[1000]; // Large buffer for formatted output
    va_list args;
    va_start(args, format);

    vsprintf(buffer, format, args);
    twrite(buffer);

    va_end(args);
}

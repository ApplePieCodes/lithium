#include <utils/halt.h>
#include <stdbool.h>

void halt() {
    __asm__ __volatile__ ("cli");
    while (true) {

    }
}
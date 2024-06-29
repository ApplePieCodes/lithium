#include "wait.h"

#define ITERATIONS_PER_MS 10000

void wait(unsigned int milliseconds) {
    volatile unsigned int count;
    while (milliseconds > 0) {
        count = ITERATIONS_PER_MS;
        while (count > 0) {
            count--;
        }
        milliseconds--;
    }
}

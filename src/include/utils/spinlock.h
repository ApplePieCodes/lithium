#pragma once
#include <stdbool.h>

typedef struct lock {
    bool locked;
} lock_t;

void spinlock_lock(lock_t *lock);
void spinlock_unlock(lock_t *lock);
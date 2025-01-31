#include <utils/spinlock.h>

void spinlock_lock(lock_t *lock) {
    while (lock->locked == true) {
        
    }
    lock->locked = true;
}

void spinlock_unlock(lock_t *lock) {
    lock->locked = false;
}
#ifndef MEMORY_H
#define MEMORY_H

#ifndef WARN_ON_MEMORY_LOCK_ERRORS
#define WARN_ON_MEMORY_LOCK_ERRORS 1
#endif

#include <sodium.h>

// This is a limit, not an allocation, so it's ok for it to be too big.
// Set it to twice the largest amount of memory we could use (see
// cryptography.c).
#define MEMLOCK_LIMIT_BYTES (crypto_pwhash_MEMLIMIT_SENSITIVE * 2)

void lock_memory_and_drop_privileges(void);

void *malloc_or_exit(size_t n, const char *what);
char *strdup_or_exit(const char *str, const char *what);
char *strndup_or_exit(const char *str, size_t n, const char *what);

#endif

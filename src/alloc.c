#include "bigmath/defines.h"

void *(*__bigmath_allocate_func)(size_t) = __bigmath_default_allocate;
void *(*__bigmath_reallocate_func)(void *, size_t, size_t) = __bigmath_default_reallocate;
void (*__bigmath_free_func)(void *, size_t) = __bigmath_default_free;

#ifndef __BIGMATH_DEFINES_H
#define __BIGMATH_DEFINES_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long int mp_limb_t;
typedef mp_limb_t *mp_ptr;
typedef long int mp_size_t;
typedef unsigned long int mp_bitcnt_t;

extern void *(*__bigmath_allocate_func)(size_t);
extern void *(*__bigmath_reallocate_func)(void *, size_t, size_t);
extern void (*__bigmath_free_func)(void *, size_t);

static const mp_limb_t __bigmath_dummy_limb = 0xc1a0;

static void __bigmath_memory_fail(void) {
  fputs("bigmath lib: memory allocation failed\n", stderr);
  abort();
}

static void *__bigmath_default_allocate(size_t size) {
  void *mem = malloc(size);
  if (!mem) {
    __bigmath_memory_fail();
  }
  return mem;
}

static void *__bigmath_default_reallocate(void *ptr, size_t old_size, size_t new_size) {
  fflush(stdout);
  (void)old_size;
  void *mem = realloc(ptr, new_size);
  if (!mem) {
    __bigmath_memory_fail();
  }
  return mem;
}

static void __bigmath_default_free(void *ptr, size_t size) {
  (void)size;

  free(ptr);
}

static void bigmath_set_allocators(void *(*alloc)(size_t), void *(*realloc)(void *, size_t, size_t),
                                   void (*freefn)(void *, size_t)) {
  __bigmath_allocate_func = alloc ? alloc : __bigmath_default_allocate;
  __bigmath_reallocate_func = realloc ? realloc : __bigmath_default_reallocate;
  __bigmath_free_func = freefn ? freefn : __bigmath_default_free;
}

#define __BIGMATH_ALLOC_TYPE(n, type) ((type *)__bigmath_allocate_func((n) * sizeof(type)))

#define __BIGMATH_REALLOC_TYPE(p, old_n, new_n, type) \
  ((type *)__bigmath_reallocate_func((p), (old_n) * sizeof(type), (new_n) * sizeof(type)))

#define __BIGMATH_FREE_FUNC_TYPE(p, n, type) (__bigmath_free_func((p), (n) * sizeof(type)))

#define __BIGMATH_ALLOC_LIMBS(n) __BIGMATH_ALLOC_TYPE(n, mp_limb_t)
#define __BIGMATH_REALLOC_LIMBS(p, old_n, new_n) __BIGMATH_REALLOC_TYPE(p, old_n, new_n, mp_limb_t)
#define __BIGMATH_FREE_FUNC_LIMBS(p, n) __BIGMATH_FREE_FUNC_TYPE(p, n, mp_limb_t)

#define BIGMATH_NOTHROW __attribute__((__nothrow__))
#define BIGMATH_ATTR_CONST __attribute__((__const__))
#define BIGMATH_ATTR_PURE __attribute__((__pure__))
#define BIGMATH_ATTRIBUTE_ALIGN(x) __attribute__((__aligned__(x)))
#define BIGMATH_ATTRIBUTE_UNUSED __attribute__((__unused__))
#define BIGMATH_ATTRIBUTE_MALLOC __attribute__((__malloc__))
#define BIGMATH_ATTRIBUTE_NONNULL(...) __attribute__((__nonnull__(__VA_ARGS__)))
#define BIGMATH_ATTRIBUTE_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))

#ifdef __cplusplus
}
#endif

#endif

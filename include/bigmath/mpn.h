#ifndef __BIGMATH_MPN_H
#define __BIGMATH_MPN_H

#include "bigmath/defines.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MPN_ABS(x) ((x) >= 0 ? (x) : -(x))

mp_limb_t mpn_add_n(mp_ptr rp, const mp_limb_t *xp, const mp_limb_t *yp, mp_size_t n) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

mp_limb_t mpn_sub_n(mp_ptr rp, const mp_limb_t *xp, const mp_limb_t *yp, mp_size_t n) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

mp_limb_t mpn_add(mp_ptr rp, const mp_limb_t *xp, mp_size_t xn, const mp_limb_t *yp, mp_size_t yn) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2, 4);

mp_limb_t mpn_sub(mp_ptr rp, const mp_limb_t *xp, mp_size_t xn, const mp_limb_t *yp, mp_size_t yn) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2, 4);

int mpn_cmp(const mp_limb_t *xp, const mp_limb_t *yp, mp_size_t n) BIGMATH_ATTR_PURE BIGMATH_ATTRIBUTE_NONNULL(1, 2);

mp_limb_t mpn_add_1(mp_ptr rp, const mp_limb_t *xp, mp_size_t n, mp_limb_t val) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2);

mp_limb_t mpn_sub_1(mp_ptr rp, const mp_limb_t *xp, mp_size_t n, mp_limb_t val) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2);

mp_limb_t mpn_mul_1(mp_ptr rp, const mp_limb_t *xp, mp_size_t n, mp_limb_t val) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2);

mp_limb_t mpn_addmul_1(mp_ptr rp, const mp_limb_t *xp, mp_size_t n, mp_limb_t val) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2);

mp_limb_t mpn_submul_1(mp_ptr rp, const mp_limb_t *xp, mp_size_t n, mp_limb_t val) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2);

void mpn_mul(mp_ptr rp, const mp_limb_t *xp, mp_size_t xn, const mp_limb_t *yp, mp_size_t yn) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2, 4);

mp_limb_t mpn_divrem(mp_ptr qp, mp_size_t qn, mp_ptr rp, mp_size_t rn, const mp_limb_t *dp,
                     mp_size_t dn) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 3, 5);

mp_limb_t mpn_lshift(mp_ptr rp, const mp_limb_t *xp, mp_size_t n, unsigned long int shift) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2);

mp_limb_t mpn_rshift(mp_ptr rp, const mp_limb_t *xp, mp_size_t n, unsigned long int shift) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2);

void mpn_and_n(mp_ptr rp, const mp_limb_t *xp, const mp_limb_t *yp, mp_size_t n) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpn_ior_n(mp_ptr rp, const mp_limb_t *xp, const mp_limb_t *yp, mp_size_t n) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpn_xor_n(mp_ptr rp, const mp_limb_t *xp, const mp_limb_t *yp, mp_size_t n) BIGMATH_NOTHROW
    BIGMATH_ATTRIBUTE_NONNULL(1, 2, 3);

void mpn_com_n(mp_ptr rp, const mp_limb_t *xp, mp_size_t n) BIGMATH_NOTHROW BIGMATH_ATTRIBUTE_NONNULL(1, 2);

size_t mpn_popcount(const mp_limb_t *xp, mp_size_t n) BIGMATH_ATTR_PURE BIGMATH_ATTRIBUTE_NONNULL(1);

size_t mpn_scan1(const mp_limb_t *xp, mp_size_t n, size_t start_bit) BIGMATH_ATTR_PURE BIGMATH_ATTRIBUTE_NONNULL(1);

#ifdef __cplusplus
}
#endif

#endif

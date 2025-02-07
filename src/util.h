#ifndef QML_SRC_UTIL_H
#define QML_SRC_UTIL_H

#include <stdlib.h>
#include <string.h>

#include <k.h>

#if KXVER > 2
#define _l  j
#define  L  J
#define KL KJ
#define kL kJ
#else
#define _l  i
#define  L  I
#define KL KI
#define kL kI
#endif


#ifdef COVERAGE
#define always(x) (1)
#else
#define always(x) (x)
#endif

#ifdef DEBUG
#define assert(x) (always(x) ? (void)0 : abort())
#else
#define assert(x) ((void)0)
#endif

#define qt(x) (assert((x)), (x)->t)
#define qn(x) (assert((x) && has_n((x))), (x)->n)

#define qt__(x, t_, v) (assert((x) && (x)->t == t_), (x)->v)
#define ql(x) qt__((x), -KL, _l)
#define qf(x) qt__((x), -KF,  f)

#define qT__(x, i, t_, T) \
    k##T((assert((x) && (x)->t == t_ && (i) >= 0 && (i) < (x)->n), (x)))[(i)]
#define qK(x, i) qT__((x), (i), 0, K)
#define qB(x, i) qT__((x), (i), KB, G)
#define qH(x, i) qT__((x), (i), KH, H)
#define qI(x, i) qT__((x), (i), KI, I)
#define qJ(x, i) qT__((x), (i), KJ, J)
#define qL(x, i) qT__((x), (i), KL, L)
#define qE(x, i) qT__((x), (i), KE, E)
#define qF(x, i) qT__((x), (i), KF, F)

// pointer to range of n typed values
#define qrT__(x, n_, t_, T) \
    k##T((assert((x) && (x)->t == t_ && (n_) >= 0 && (n_) <= (x)->n), (x)))
#define qrF(x, i) qrT__((x), (i), KF, F)

#define q0(x) (assert((x)), r0((x)), (x) = NULL, (void)0)


#if __GNUC__ >= 3
    #define likely(x) __builtin_expect(!!(x), 1)
#else
    #define likely(x) (x)
#endif

#define check(x, r, c)      \
    do                      \
        if (!likely((x))) { \
            c;              \
            return (r);     \
        }                   \
    while (0)

#define check_type(x, c)    check(x, krr("type"),   c)
#define check_length(x, c)  check(x, krr("length"), c)

// n may be negative
#define repeat(i, n) \
    for (L i = 0, n__##i = (n); i < n__##i; i++)
#define repeati(i, n) \
    for (I i = 0, n__##i = (n); i < n__##i; i++)
#define repeati_(i, i0, n) \
    for (I i = (i0), n__##i = (n); i < n__##i; i++)


static inline int
has_n(K x) {
    return qt(x) >= 0 && qt(x) < XT;
}

static inline int
callable(K x) {
    return qt(x) >= 100;
}


int compatible_i(K x);
int compatible_f(K x);
I convert_i(K x);
F convert_f(K x);

// NULL if not compatible
K convert_F(K x);
K convert_FF(K x);
K convert_FFF(K x);

int item_I(I* r, K x, L i);
int item_F(F* r, K x, L i);


// dst or src may be null if n=0
static inline void
copy_F(F* dst_base, L dst_offs, const F* src_base, L src_offs, L n) {
    // memcpy on null, even with 0 size, is undefined
    // pointer arithmetic on null is undefined
    if (n)
        memcpy(dst_base + dst_offs,
               src_base + src_offs, n * sizeof(F));
}

K make_F_null(L n);
K make_F(const F* a_base, L a_offs, L n);


K new_D();
void append_D(K x, S k, K v);


static inline I min_i(I x, I y) { return x <= y ? x : y; }
static inline I max_i(I x, I y) { return x >= y ? x : y; }

static inline void swap_i(I* x, I* y) { I t = *x; *x = *y; *y = t; }
static inline void swap_l(L* x, L* y) { L t = *x; *x = *y; *y = t; }
static inline void swap_f(F* x, F* y) { F t = *x; *x = *y; *y = t; }


static inline K
check_err(K x, S err) {
    if (!likely(!err)) {
        q0(x);
        return krr(err);
    } else
        return x;
}


#endif // QML_SRC_UTIL_H

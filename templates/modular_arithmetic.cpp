#define MOD 1000000007

namespace mod_op {
    long long mpow(long long base, long long exponent) {
        long long res = 1;
        while (exponent > 0) {
            if (exponent & 1) {
                res = (res * base) % MOD;
            }
            base = (base * base) % MOD;
            exponent = exponent >> 1;
        }
        return res;
    }

    long long minv(long long base) {
        return mpow(base, MOD - 2);
    }
}
using namespace mod_op;
#ifndef SPROUT_RANDOM_CONST_MOD_HPP
#define SPROUT_RANDOM_CONST_MOD_HPP

#include <type_traits>
#include <limits>
#include <sprout/config.hpp>

namespace sprout {
	namespace random {
		namespace detail {
			template<typename IntType, IntType m>
			class const_mod {
			private:
				typedef typename std::make_unsigned<IntType>::type unsigned_type;
			private:
				SPROUT_STATIC_CONSTEXPR IntType suppress_warnings = m == 0;
				SPROUT_STATIC_CONSTEXPR IntType modulus = m + suppress_warnings;
			private:
				static_assert(suppress_warnings == 0, "suppress_warnings == 0");
				static_assert(modulus == m, "modulus == m");
			private:
				static SPROUT_CONSTEXPR IntType pow_1(IntType a, std::uintmax_t exponent, IntType result = 1) {
					return exponent != 0
						? pow_1(mult(a, a), exponent / 2, exponent % 2 == 1 ? mult(result, a) : result)
						: result
						;
				}
				static SPROUT_CONSTEXPR IntType mult_small(IntType a, IntType x) {
					return a * x % (m + suppress_warnings);
				}
				static SPROUT_CONSTEXPR IntType mult_schrage_1(IntType a, IntType value, IntType q, IntType r) {
					return r < q
						? sub(a * (value % q), r * (value / q))
						: throw "assert(r < q)"
						;
				}
				static SPROUT_CONSTEXPR IntType mult_schrage(IntType a, IntType value) {
					return mult_schrage_1(a, value, m / a, m % a);
				}
				static SPROUT_CONSTEXPR IntType mult_general(IntType a, IntType b) {
					return std::uintmax_t(modulus) <= std::numeric_limits<std::uintmax_t>::max() / modulus
						? static_cast<IntType>(std::uintmax_t(a) * b % modulus)
						: /*static_cast<IntType>(sprout::random::detail::mulmod(a, b, modulus))*/throw "Sorry, not implemented."
						;
				}
				static SPROUT_CONSTEXPR IntType sub(IntType a, IntType b) {
					return a < b ? m - (b - a) : a - b;
				}
				static SPROUT_CONSTEXPR unsigned_type unsigned_m() {
					return m == 0 ? unsigned_type((std::numeric_limits<IntType>::max)()) + 1 : unsigned_type(m);
				}
				static SPROUT_CONSTEXPR IntType invert_euclidian_3(IntType c, IntType l1, IntType l2, IntType n, IntType p) {
					return n == 0 ? m - l1 : invert_euclidian_1(c, l1, l2, n, p);
				}
				static SPROUT_CONSTEXPR IntType invert_euclidian_2(IntType c, IntType l1, IntType l2, IntType n, IntType p) {
					return p == 0 ? l2 : invert_euclidian_3(c, l1, l2 + (n / p) * l1, n - (n / p) * p, p);
				}
				static SPROUT_CONSTEXPR IntType invert_euclidian_1(IntType c, IntType l1, IntType l2, IntType n, IntType p) {
					return invert_euclidian_2(c, l1 + (p / n) * l2, l2, n, p - (p / n) * n);
				}
				static SPROUT_CONSTEXPR IntType invert_euclidian(IntType c) {
					return c > 0
						? c == 1 ? 1 : invert_euclidian_1(c, 0, 1, c, m)
						: throw "assert(c > 0)"
						;
				}
				static SPROUT_CONSTEXPR IntType invert_euclidian0_3(IntType c, IntType l1, IntType l2, IntType n, IntType p) {
					return n == 0 ? m - l1 : invert_euclidian0_2(c, l1 + (p / n) * l2, l2, n, p - (p / n) * n);
				}
				static SPROUT_CONSTEXPR IntType invert_euclidian0_2(IntType c, IntType l1, IntType l2, IntType n, IntType p) {
					return p == 0 ? l2 : invert_euclidian0_3(c, l1, l2 + (n / p) * l1, n - (n / p) * p, p);
				}
				static SPROUT_CONSTEXPR IntType invert_euclidian0_1(IntType c, IntType l1, IntType l2, IntType n, IntType p) {
					return std::numeric_limits<IntType>::max() % n != n - 1
						? invert_euclidian0_2(c, l1 + (std::numeric_limits<IntType>::max() / n) * l2, l2, n, std::numeric_limits<IntType>::max() - (std::numeric_limits<IntType>::max() / n) * n + 1)
						: throw "assert(std::numeric_limits<IntType>::max() % n != n - 1)"
						;
				}
				static SPROUT_CONSTEXPR IntType invert_euclidian0(IntType c) {
					return c > 0
						? c == 1 ? 1 : invert_euclidian0_1(c, 0, 1, c, m)
						: throw "assert(c > 0)"
						;
				}
			public:
				static SPROUT_CONSTEXPR IntType apply(IntType x) {
					return ((unsigned_m() - 1) & unsigned_m()) == 0
						? (unsigned_type(x)) & (unsigned_m() - 1)
						: x % (m + suppress_warnings)
						;
				}
				static SPROUT_CONSTEXPR IntType add(IntType x, IntType c) {
					return ((unsigned_m() - 1) & unsigned_m()) == 0 ? (unsigned_type(x) + unsigned_type(c)) & (unsigned_m() - 1)
						: c == 0 ? x
						: x < m - c ? x + c
						: x - (m - c)
						;
				}
				static SPROUT_CONSTEXPR IntType mult(IntType a, IntType x) {
					return ((unsigned_m() - 1) & unsigned_m()) == 0 ? unsigned_type(a) * unsigned_type(x) & (unsigned_m() - 1)
						: a == 0 ? 0
						: a == 1 ? x
						: m <= std::numeric_limits<IntType>::max() / a ? mult_small(a, x)
						: std::numeric_limits<IntType>::is_signed && (m % a < m / a) ? mult_schrage(a, x)
						: mult_general(a, x)
						;
				}
				static SPROUT_CONSTEXPR IntType mult_add(IntType a, IntType x, IntType c) {
					return ((unsigned_m() - 1) & unsigned_m()) == 0 ? (unsigned_type(a) * unsigned_type(x) + unsigned_type(c)) & (unsigned_m() - 1)
						: a == 0 ? c
						: m <= (std::numeric_limits<IntType>::max() - c) / a ? (a * x + c) % (m + suppress_warnings)
						: add(mult(a, x), c)
						;
				}
				static SPROUT_CONSTEXPR IntType pow(IntType a, std::uintmax_t exponent) {
					return pow_1(a, exponent);
				}
				static SPROUT_CONSTEXPR IntType invert(IntType x) {
					return x == 0 ? 0
						: m == 0 ? invert_euclidian0(x)
						: invert_euclidian(x)
						;
				}
			private:
				const_mod() = delete;
			};
		} // namespace detail
	} // namespace random
} // namespace sprout

#endif // #ifndef SPROUT_RANDOM_CONST_MOD_HPP


#ifndef SPROUT_RANDOM_LINEAR_CONGRUENTIAL_HPP
#define SPROUT_RANDOM_LINEAR_CONGRUENTIAL_HPP

#include <cstdint>
#include <limits>
#include <ios>
#include <sprout/config.hpp>
#include <sprout/random/detail/const_mod.hpp>
#include <sprout/random/random_result.hpp>

namespace sprout {
	namespace random {
		//
		// linear_congruential_engine
		//
		template<typename IntType, IntType a, IntType c, IntType m>
		class linear_congruential_engine {
		public:
			typedef IntType result_type;
		private:
			struct private_constructor_tag {};
		public:
			SPROUT_STATIC_CONSTEXPR IntType multiplier = a;
			SPROUT_STATIC_CONSTEXPR IntType increment = c;
			SPROUT_STATIC_CONSTEXPR IntType modulus = m;
			SPROUT_STATIC_CONSTEXPR IntType default_seed = 1;
		public:
			static_assert(std::numeric_limits<IntType>::is_integer, "std::numeric_limits<IntType>::is_integer");
			static_assert(m == 0 || a < m, "m == 0 || a < m");
			static_assert(m == 0 || c < m, "m == 0 || c < m");
		private:
			static SPROUT_CONSTEXPR IntType init_seed_3(IntType const& x0) {
				return x0 >= static_min() && x0 <= static_max()
					? x0
					: throw "assert(x0 >= static_min() && x0 <= static_max())"
					;
			}
			static SPROUT_CONSTEXPR IntType init_seed_2(IntType const& x0) {
				return init_seed_3(increment == 0 && x0 == 0 ? 1 : x0);
			}
			static SPROUT_CONSTEXPR IntType init_seed_1(IntType const& x0) {
				return init_seed_2(x0 <= 0 && x0 != 0 ? x0 + modulus : x0);
			}
			static SPROUT_CONSTEXPR IntType init_seed(IntType const& x0) {
				return init_seed_1(modulus == 0 ? x0 : x0 % modulus);
			}
		public:
			static SPROUT_CONSTEXPR result_type static_min() {
				return c == 0 ? 1 : 0;
			}
			static SPROUT_CONSTEXPR result_type static_max() {
				return modulus - 1;
			}
		private:
			IntType x_;
		private:
			SPROUT_CONSTEXPR linear_congruential_engine(IntType const& x, private_constructor_tag)
				: x_(x)
			{}
			SPROUT_CONSTEXPR sprout::random::random_result<linear_congruential_engine> generate(result_type result) const {
				return sprout::random::random_result<linear_congruential_engine>(
					result,
					linear_congruential_engine(result, private_constructor_tag())
					);
			}
		public:
			SPROUT_CONSTEXPR linear_congruential_engine()
				//: x_(init_seed(default_seed))	// ???
				: x_(init_seed(1))	// ???
			{}
			SPROUT_CONSTEXPR explicit linear_congruential_engine(IntType const& x0)
				: x_(init_seed(x0))
			{}
			SPROUT_CONSTEXPR result_type min() const {
				return static_min();
			}
			SPROUT_CONSTEXPR result_type max() const {
				return static_max();
			}
			SPROUT_CONSTEXPR sprout::random::random_result<linear_congruential_engine> operator()() const {
				return generate(sprout::random::detail::const_mod<IntType, m>::mult_add(a, x_, c));
			}
			friend SPROUT_CONSTEXPR bool operator==(linear_congruential_engine const& lhs, linear_congruential_engine const& rhs) {
				return lhs.x_ == rhs.x_;
			}
			friend SPROUT_CONSTEXPR bool operator!=(linear_congruential_engine const& lhs, linear_congruential_engine const& rhs) {
				return !(lhs == rhs);
			}
			template<typename Elem, typename Traits>
			friend std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				linear_congruential_engine const& rhs
				)
			{
				IntType x;
				if(lhs >> x) {
					if(x >= min() && x <= max()) {
						rhs.x_ = x;
					} else {
						lhs.setstate(std::ios_base::failbit);
					}
				}
				return lhs;
			}
			template<typename Elem, typename Traits>
			friend std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				linear_congruential_engine const& rhs
				)
			{
				return lhs << rhs.x_;
			}
		};

		//
		// minstd_rand0
		//
		typedef sprout::random::linear_congruential_engine<std::uint32_t, 16807, 0, 2147483647> minstd_rand0;
		//
		// minstd_rand
		//
		typedef sprout::random::linear_congruential_engine<std::uint32_t, 48271, 0, 2147483647> minstd_rand;
	} // namespace random

	using sprout::random::minstd_rand0;
	using sprout::random::minstd_rand;
} // namespace sprout

#endif // #ifndef SPROUT_RANDOM_LINEAR_CONGRUENTIAL_HPP


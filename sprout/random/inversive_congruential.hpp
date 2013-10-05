/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_INVERSIVE_CONGRUENTIAL_HPP
#define SPROUT_RANDOM_INVERSIVE_CONGRUENTIAL_HPP

#include <cstdint>
#include <ios>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/random/detail/const_mod.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/math/greater_equal.hpp>
#include <sprout/assert.hpp>

namespace sprout {
	namespace random {
		//
		// inversive_congruential_engine
		//
		template<typename IntType, IntType a, IntType b, IntType p>
		class inversive_congruential_engine {
		public:
			typedef IntType result_type;
		private:
			struct private_construct_t {};
		public:
			SPROUT_STATIC_CONSTEXPR IntType multiplier = a;
			SPROUT_STATIC_CONSTEXPR IntType increment = b;
			SPROUT_STATIC_CONSTEXPR IntType modulus = p;
			SPROUT_STATIC_CONSTEXPR IntType default_seed = 1;
		public:
			static SPROUT_CONSTEXPR result_type static_min() SPROUT_NOEXCEPT {
				return b == 0 ? 1 : 0;
			}
			static SPROUT_CONSTEXPR result_type static_max() SPROUT_NOEXCEPT {
				return modulus - 1;
			}
			static SPROUT_CONSTEXPR IntType init_seed_3(IntType const& x0) {
				return SPROUT_ASSERT(sprout::math::greater_equal(x0, static_min())), SPROUT_ASSERT(x0 <= static_max()), x0;
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
		private:
			IntType x_;
		private:
			SPROUT_CONSTEXPR inversive_congruential_engine(IntType const& x, private_construct_t)
				: x_(x)
			{}
			SPROUT_CONSTEXPR sprout::random::random_result<inversive_congruential_engine>
			generate(result_type result) const {
				return sprout::random::random_result<inversive_congruential_engine>(
					result,
					inversive_congruential_engine(result, private_construct_t())
					);
			}
		public:
			SPROUT_CONSTEXPR inversive_congruential_engine()
				: x_(init_seed(default_seed))
			{}
			explicit SPROUT_CONSTEXPR inversive_congruential_engine(IntType const& x0)
				: x_(init_seed(x0))
			{}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return static_min();
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return static_max();
			}
			SPROUT_CONSTEXPR sprout::random::random_result<inversive_congruential_engine> operator()() const {
				typedef sprout::random::detail::const_mod<IntType, p> do_mod;
				return generate(do_mod::mult_add(a, do_mod::invert(x_), b));
			}
			friend SPROUT_CONSTEXPR bool operator==(inversive_congruential_engine const& lhs, inversive_congruential_engine const& rhs) SPROUT_NOEXCEPT {
				return lhs.x_ == rhs.x_;
			}
			friend SPROUT_CONSTEXPR bool operator!=(inversive_congruential_engine const& lhs, inversive_congruential_engine const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
			template<typename Elem, typename Traits>
			friend std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				inversive_congruential_engine& rhs
				)
			{
				IntType x;
				if (lhs >> x) {
					if (sprout::math::greater_equal(x, static_min()) && x <= static_max()) {
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
				inversive_congruential_engine const& rhs
				)
			{
				return lhs << rhs.x_;
			}
		};
		template<typename IntType, IntType a, IntType b, IntType p>
		SPROUT_CONSTEXPR_OR_CONST IntType sprout::random::inversive_congruential_engine<IntType, a, b, p>::multiplier;
		template<typename IntType, IntType a, IntType b, IntType p>
		SPROUT_CONSTEXPR_OR_CONST IntType sprout::random::inversive_congruential_engine<IntType, a, b, p>::increment;
		template<typename IntType, IntType a, IntType b, IntType p>
		SPROUT_CONSTEXPR_OR_CONST IntType sprout::random::inversive_congruential_engine<IntType, a, b, p>::modulus;
		template<typename IntType, IntType a, IntType b, IntType p>
		SPROUT_CONSTEXPR_OR_CONST IntType sprout::random::inversive_congruential_engine<IntType, a, b, p>::default_seed;

		//
		// hellekalek1995
		//
		typedef sprout::random::inversive_congruential_engine<std::uint32_t, 9102, 2147483647 - 36884165, 2147483647> hellekalek1995;
	}	// namespace random

	using sprout::random::inversive_congruential_engine;
	using sprout::random::hellekalek1995;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_INVERSIVE_CONGRUENTIAL_HPP

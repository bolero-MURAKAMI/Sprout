/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_LINEAR_CONGRUENTIAL_HPP
#define SPROUT_RANDOM_LINEAR_CONGRUENTIAL_HPP

#include <cstdint>
#include <ios>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/random/detail/const_mod.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/math/comparison.hpp>
#include <sprout/assert.hpp>

namespace sprout {
	namespace random {
		//
		// linear_congruential_engine
		//
		template<typename UIntType, UIntType a, UIntType c, UIntType m>
		class linear_congruential_engine {
			static_assert(sprout::numeric_limits<UIntType>::is_integer, "sprout::numeric_limits<UIntType>::is_integer");
			static_assert(m == 0 || a < m, "m == 0 || a < m");
			static_assert(m == 0 || c < m, "m == 0 || c < m");
		public:
			typedef UIntType result_type;
		private:
			struct private_constructor_tag {};
		public:
			SPROUT_STATIC_CONSTEXPR UIntType multiplier = a;
			SPROUT_STATIC_CONSTEXPR UIntType increment = c;
			SPROUT_STATIC_CONSTEXPR UIntType modulus = m;
			SPROUT_STATIC_CONSTEXPR UIntType default_seed = 1;
		public:
			static SPROUT_CONSTEXPR result_type static_min() SPROUT_NOEXCEPT {
				return c == 0 ? 1 : 0;
			}
			static SPROUT_CONSTEXPR result_type static_max() SPROUT_NOEXCEPT {
				return m - 1;
			}
		private:
			static SPROUT_CONSTEXPR UIntType init_seed_3(UIntType const& x0) {
				return SPROUT_ASSERT(sprout::math::greater_equal(x0, static_min())), SPROUT_ASSERT(x0 <= static_max()), x0;
			}
			static SPROUT_CONSTEXPR UIntType init_seed_2(UIntType const& x0) {
				return init_seed_3(increment == 0 && x0 == 0 ? 1 : x0);
			}
			static SPROUT_CONSTEXPR UIntType init_seed_1(UIntType const& x0) {
				return init_seed_2(x0 <= 0 && x0 != 0 ? x0 + modulus : x0);
			}
			static SPROUT_CONSTEXPR UIntType init_seed(UIntType const& x0) {
				return init_seed_1(modulus == 0 ? x0 : x0 % modulus);
			}
		private:
			UIntType x_;
		private:
			SPROUT_CONSTEXPR linear_congruential_engine(UIntType const& x, private_constructor_tag)
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
				: x_(init_seed(default_seed))
			{}
			explicit SPROUT_CONSTEXPR linear_congruential_engine(UIntType const& x0)
				: x_(init_seed(x0))
			{}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return static_min();
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return static_max();
			}
			SPROUT_CONSTEXPR sprout::random::random_result<linear_congruential_engine> operator()() const {
				return generate(sprout::random::detail::const_mod<UIntType, m>::mult_add(a, x_, c));
			}
			friend SPROUT_CONSTEXPR bool operator==(linear_congruential_engine const& lhs, linear_congruential_engine const& rhs) SPROUT_NOEXCEPT {
				return lhs.x_ == rhs.x_;
			}
			friend SPROUT_CONSTEXPR bool operator!=(linear_congruential_engine const& lhs, linear_congruential_engine const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
			template<typename Elem, typename Traits>
			friend std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				linear_congruential_engine& rhs
				)
			{
				UIntType x;
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
				linear_congruential_engine const& rhs
				)
			{
				return lhs << rhs.x_;
			}
		};
		template<typename UIntType, UIntType a, UIntType c, UIntType m>
		SPROUT_CONSTEXPR_OR_CONST UIntType sprout::random::linear_congruential_engine<UIntType, a, c, m>::multiplier;
		template<typename UIntType, UIntType a, UIntType c, UIntType m>
		SPROUT_CONSTEXPR_OR_CONST UIntType sprout::random::linear_congruential_engine<UIntType, a, c, m>::increment;
		template<typename UIntType, UIntType a, UIntType c, UIntType m>
		SPROUT_CONSTEXPR_OR_CONST UIntType sprout::random::linear_congruential_engine<UIntType, a, c, m>::modulus;
		template<typename UIntType, UIntType a, UIntType c, UIntType m>
		SPROUT_CONSTEXPR_OR_CONST UIntType sprout::random::linear_congruential_engine<UIntType, a, c, m>::default_seed;

		//
		// minstd_rand0
		//
		typedef sprout::random::linear_congruential_engine<std::uint32_t, 16807, 0, 2147483647> minstd_rand0;
		//
		// minstd_rand
		//
		typedef sprout::random::linear_congruential_engine<std::uint32_t, 48271, 0, 2147483647> minstd_rand;

		//
		// rand48
		//
		class rand48 {
		public:
			typedef std::uint32_t result_type;
		private:
			struct private_constructor_tag {};
			typedef sprout::random::linear_congruential_engine<
				std::uint64_t,
				std::uint64_t(0xDEECE66DUL) | (std::uint64_t(0x5) << 32),
				0xB,
				std::uint64_t(1) << 48
			> lcf_type;
		private:
			static SPROUT_CONSTEXPR result_type static_min() {
				return 0;
			}
			static SPROUT_CONSTEXPR result_type static_max() {
				return 0x7FFFFFFF;
			}
			static SPROUT_CONSTEXPR std::uint64_t cnv(std::uint32_t x) {
				return (static_cast<std::uint64_t>(x) << 16) | 0x330e;
			}
		private:
			lcf_type lcf_;
		private:
			SPROUT_CONSTEXPR rand48(lcf_type const& lcf, private_constructor_tag)
				: lcf_(lcf)
			{}
			SPROUT_CONSTEXPR sprout::random::random_result<rand48> generate(
				sprout::random::random_result<lcf_type> const& lcf_result
				) const
			{
				return sprout::random::random_result<rand48>(
					lcf_result.result() >> 17,
					rand48(lcf_result.engine(), private_constructor_tag())
					);
			}
		public:
			SPROUT_CONSTEXPR rand48()
				: lcf_(cnv(static_cast<std::uint32_t>(1)))
			{}
			explicit SPROUT_CONSTEXPR rand48(result_type const& x0)
				: lcf_(cnv(x0))
			{}
			SPROUT_CONSTEXPR result_type min() const {
				return static_min();
			}
			SPROUT_CONSTEXPR result_type max() const {
				return static_max();
			}
			SPROUT_CONSTEXPR sprout::random::random_result<rand48> operator()() const {
				return generate(lcf_());
			}
			friend SPROUT_CONSTEXPR bool operator==(rand48 const& lhs, rand48 const& rhs) {
				return lhs.lcf_ == rhs.lcf_;
			}
			friend SPROUT_CONSTEXPR bool operator!=(rand48 const& lhs, rand48 const& rhs) {
				return !(lhs == rhs);
			}
			template<typename Elem, typename Traits>
			friend std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				rand48& rhs
				)
			{
				return lhs >> rhs.lcf_;
			}
			template<typename Elem, typename Traits>
			friend std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				rand48 const& rhs
				)
			{
				return lhs << rhs.lcf_;
			}
		};
	}	// namespace random

	using sprout::random::linear_congruential_engine;
	using sprout::random::minstd_rand0;
	using sprout::random::minstd_rand;
	using sprout::random::rand48;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_LINEAR_CONGRUENTIAL_HPP

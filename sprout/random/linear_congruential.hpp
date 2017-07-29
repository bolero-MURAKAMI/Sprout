/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_LINEAR_CONGRUENTIAL_HPP
#define SPROUT_RANDOM_LINEAR_CONGRUENTIAL_HPP

#include <cstdint>
#include <istream>
#include <ostream>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/random/detail/const_mod.hpp>
#include <sprout/random/detail/seed_impl.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/type_traits.hpp>
#include <sprout/random/results.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/greater_equal.hpp>
#include <sprout/utility/while_loop.hpp>
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
			struct private_construct_t {};
		public:
			SPROUT_STATIC_CONSTEXPR result_type multiplier = a;
			SPROUT_STATIC_CONSTEXPR result_type increment = c;
			SPROUT_STATIC_CONSTEXPR result_type modulus = m;
			SPROUT_STATIC_CONSTEXPR result_type default_seed = 1;
		public:
			static SPROUT_CONSTEXPR result_type static_min() SPROUT_NOEXCEPT {
				return increment == 0 ? 1 : 0;
			}
			static SPROUT_CONSTEXPR result_type static_max() SPROUT_NOEXCEPT {
				return modulus - 1;
			}
		private:
			static SPROUT_CONSTEXPR result_type init_seed_3(result_type x0) {
				return SPROUT_ASSERT(sprout::math::greater_equal(x0, static_min())), SPROUT_ASSERT(x0 <= static_max()), x0;
			}
			static SPROUT_CONSTEXPR result_type init_seed_2(result_type x0) {
				return init_seed_3(increment == 0 && x0 == 0 ? 1 : x0);
			}
			static SPROUT_CONSTEXPR result_type init_seed_1(result_type x0) {
				return init_seed_2(x0 <= 0 && x0 != 0 ? x0 + modulus : x0);
			}
			static SPROUT_CONSTEXPR result_type init_seed(result_type x0 = default_seed) {
				return init_seed_1(modulus == 0 ? x0 : x0 % modulus);
			}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			static SPROUT_CXX14_CONSTEXPR result_type init_seed(Sseq& seq) {
				return init_seed(sprout::random::detail::seed_one_int<result_type, modulus>(seq));
			}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			static SPROUT_CONSTEXPR result_type init_seed(Sseq const& seq) {
				return init_seed(sprout::random::detail::seed_one_int<result_type, modulus>(seq));
			}
			template<typename InputIterator>
			static SPROUT_CONSTEXPR result_type init_seed(InputIterator first, InputIterator last) {
				return init_seed(sprout::random::detail::get_one_int<result_type, modulus>(first, last));
			}
		private:
			result_type x_;
		private:
			SPROUT_CONSTEXPR linear_congruential_engine(result_type x, private_construct_t)
				: x_(x)
			{}
			SPROUT_CONSTEXPR sprout::random::random_result<linear_congruential_engine> generate(result_type result) const {
				return sprout::random::random_result<linear_congruential_engine>(
					result,
					linear_congruential_engine(result, private_construct_t())
					);
			}
			struct discard_init {
			public:
				unsigned long long exponent;
				result_type b_gcd;
				result_type a_zm1_over_gcd;
				result_type a_km1_over_gcd;
			};
			struct discard_pred {
			public:
				SPROUT_CONSTEXPR bool operator()(discard_init const& init) const {
					return static_cast<bool>(init.exponent);
				}
			};
			struct discard_op {
			public:
				SPROUT_CONSTEXPR discard_init operator()(discard_init const& init) const {
					typedef sprout::random::detail::const_mod<result_type, modulus> mod_type;
					return discard_init{
						init.exponent / 2,
						init.b_gcd,
						!(init.exponent % 2 == 1) ? init.a_zm1_over_gcd
							: mod_type::mult_add(
								init.b_gcd,
								mod_type::mult(init.a_zm1_over_gcd, init.a_km1_over_gcd),
								mod_type::add(init.a_zm1_over_gcd, init.a_km1_over_gcd)
								)
							,
						mod_type::mult_add(
							init.b_gcd,
							mod_type::mult(init.a_km1_over_gcd, init.a_km1_over_gcd),
							mod_type::add(init.a_km1_over_gcd, init.a_km1_over_gcd)
							)
						};
				}
			};
			SPROUT_CONSTEXPR linear_congruential_engine const discard_impl_1_2(result_type b_gcd, result_type a_zm1_over_gcd) const {
				typedef sprout::random::detail::const_mod<result_type, modulus> mod_type;
				return linear_congruential_engine(
					mod_type::mult_add(
						mod_type::mult_add(b_gcd, a_zm1_over_gcd, 1),
						x_,
						mod_type::mult(mod_type::invert((multiplier - 1) / b_gcd), mod_type::mult(increment, a_zm1_over_gcd))
						),
					private_construct_t()
					);
			}
			SPROUT_CONSTEXPR linear_congruential_engine const discard_impl_1_1(result_type b_inv, result_type a_z) const {
				typedef sprout::random::detail::const_mod<result_type, modulus> mod_type;
				return linear_congruential_engine(
					mod_type::mult_add(a_z, x_, mod_type::mult(mod_type::mult(increment, b_inv), a_z - 1)),
					private_construct_t()
					);
			}
			SPROUT_CONSTEXPR linear_congruential_engine const discard_impl_1(unsigned long long z, result_type b_inv, result_type b_gcd) const {
				typedef sprout::random::detail::const_mod<result_type, modulus> mod_type;
				return b_gcd == 1 ? discard_impl_1_1(b_inv, mod_type::pow(multiplier, z))
					: discard_impl_1_2(
						b_gcd,
						sprout::while_loop(
							discard_init{z, b_gcd, 0, (multiplier - 1) / b_gcd},
							discard_pred(),
							discard_op()
							).a_zm1_over_gcd
						)
					;
			}
			SPROUT_CONSTEXPR linear_congruential_engine const discard_impl(unsigned long long z, result_type b_inv) const {
				typedef sprout::random::detail::const_mod<result_type, modulus> mod_type;
				return discard_impl_1(
					z, b_inv,
					mod_type::mult(multiplier - 1, b_inv)
					);
			}
		public:
			SPROUT_CONSTEXPR linear_congruential_engine()
				: x_(init_seed())
			{}
			linear_congruential_engine(linear_congruential_engine const&) = default;
			explicit SPROUT_CONSTEXPR linear_congruential_engine(result_type x0)
				: x_(init_seed(x0))
			{}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			explicit SPROUT_CXX14_CONSTEXPR linear_congruential_engine(Sseq& seq)
				: x_(init_seed(seq))
			{}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			explicit SPROUT_CONSTEXPR linear_congruential_engine(Sseq const& seq)
				: x_(init_seed(seq))
			{}
			template<typename InputIterator>
			SPROUT_CONSTEXPR linear_congruential_engine(InputIterator first, InputIterator last)
				: x_(init_seed(first, last))
			{}
			SPROUT_CXX14_CONSTEXPR void seed(result_type x0 = default_seed) {
				x_ = init_seed(x0);
			}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			SPROUT_CXX14_CONSTEXPR void seed(Sseq& seq) {
				x_ = init_seed(seq);
			}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			SPROUT_CXX14_CONSTEXPR void seed(Sseq const& seq) {
				x_ = init_seed(seq);
			}
			template<typename InputIterator>
			SPROUT_CXX14_CONSTEXPR void seed(InputIterator first, InputIterator last) {
				x_ = init_seed(first, last);
			}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return static_min();
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return static_max();
			}
			SPROUT_CXX14_CONSTEXPR result_type operator()() {
				x_ = sprout::random::detail::const_mod<result_type, modulus>::mult_add(a, x_, c);
				return x_;
			}
			SPROUT_CONSTEXPR sprout::random::random_result<linear_congruential_engine> const operator()() const {
				return generate(sprout::random::detail::const_mod<result_type, modulus>::mult_add(a, x_, c));
			}
			SPROUT_CONSTEXPR linear_congruential_engine const discard(unsigned long long z) const {
				typedef sprout::random::detail::const_mod<result_type, modulus> mod_type;
				return discard_impl(z, mod_type::invert(multiplier - 1));
			}
			SPROUT_CXX14_CONSTEXPR void discard(unsigned long long z) {
				typedef sprout::random::detail::const_mod<result_type, modulus> mod_type;
				result_type b_inv = mod_type::invert(multiplier - 1);
				result_type b_gcd = mod_type::mult(multiplier - 1, b_inv);
				if (b_gcd == 1) {
					result_type a_z = mod_type::pow(multiplier, z);
					x_ = mod_type::mult_add(a_z, x_, mod_type::mult(mod_type::mult(increment, b_inv), a_z - 1));
				} else {
					result_type a_zm1_over_gcd = 0;
					result_type a_km1_over_gcd = (multiplier - 1) / b_gcd;
					unsigned long long exponent = z;
					while (exponent) {
						if (exponent % 2 == 1) {
							a_zm1_over_gcd = mod_type::mult_add(
								b_gcd,
								mod_type::mult(a_zm1_over_gcd, a_km1_over_gcd),
								mod_type::add(a_zm1_over_gcd, a_km1_over_gcd)
								);
						}
						a_km1_over_gcd = mod_type::mult_add(
							b_gcd,
							mod_type::mult(a_km1_over_gcd, a_km1_over_gcd),
							mod_type::add(a_km1_over_gcd, a_km1_over_gcd)
							);
						exponent /= 2;
					}
					x_ = mod_type::mult_add(
						mod_type::mult_add(b_gcd, a_zm1_over_gcd, 1),
						x_,
						mod_type::mult(mod_type::invert((multiplier - 1) / b_gcd), mod_type::mult(increment, a_zm1_over_gcd))
						);
				}
			}
			friend SPROUT_CONSTEXPR bool operator==(linear_congruential_engine const& lhs, linear_congruential_engine const& rhs) SPROUT_NOEXCEPT {
				return lhs.x_ == rhs.x_;
			}
			friend SPROUT_CONSTEXPR bool operator!=(linear_congruential_engine const& lhs, linear_congruential_engine const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				linear_congruential_engine& rhs
				)
			{
				result_type x;
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
			friend SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>& operator<<(
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
		// minstd_rand
		//
		typedef sprout::random::linear_congruential_engine<std::uint_fast32_t, 16807, 0, 2147483647> minstd_rand0;
		typedef sprout::random::linear_congruential_engine<std::uint_fast32_t, 48271, 0, 2147483647> minstd_rand;

		//
		// rand48
		//
		class rand48 {
		public:
			typedef std::uint32_t result_type;
		private:
			struct private_construct_t {};
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
			SPROUT_CONSTEXPR rand48(lcf_type const& lcf, private_construct_t)
				: lcf_(lcf)
			{}
			template<typename EngineResult>
			SPROUT_CONSTEXPR sprout::random::random_result<rand48> generate(EngineResult const& rnd) const {
				return sprout::random::random_result<rand48>(
					static_cast<result_type>(sprout::random::result(rnd)) >> 17,
					rand48(sprout::random::next(rnd), private_construct_t())
					);
			}
		public:
			SPROUT_CONSTEXPR rand48()
				: lcf_(cnv(static_cast<std::uint32_t>(1)))
			{}
			explicit SPROUT_CONSTEXPR rand48(result_type x0)
				: lcf_(cnv(x0))
			{}
			SPROUT_CONSTEXPR result_type min() const {
				return static_min();
			}
			SPROUT_CONSTEXPR result_type max() const {
				return static_max();
			}
			SPROUT_CXX14_CONSTEXPR result_type operator()() {
				return static_cast<result_type>(static_cast<result_type>(lcf_()) >> 17);
			}
			SPROUT_CONSTEXPR sprout::random::random_result<rand48> const operator()() const {
				return generate(lcf_());
			}
			friend SPROUT_CONSTEXPR bool operator==(rand48 const& lhs, rand48 const& rhs) {
				return lhs.lcf_ == rhs.lcf_;
			}
			friend SPROUT_CONSTEXPR bool operator!=(rand48 const& lhs, rand48 const& rhs) {
				return !(lhs == rhs);
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				rand48& rhs
				)
			{
				return lhs >> rhs.lcf_;
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>& operator<<(
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

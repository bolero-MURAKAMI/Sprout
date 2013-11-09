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
#include <sprout/random/detail/seed_impl.hpp>
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
			SPROUT_STATIC_CONSTEXPR result_type multiplier = a;
			SPROUT_STATIC_CONSTEXPR result_type increment = b;
			SPROUT_STATIC_CONSTEXPR result_type modulus = p;
			SPROUT_STATIC_CONSTEXPR result_type default_seed = 1;
		public:
			static SPROUT_CONSTEXPR result_type static_min() SPROUT_NOEXCEPT {
				return increment == 0 ? 1 : 0;
			}
			static SPROUT_CONSTEXPR result_type static_max() SPROUT_NOEXCEPT {
				return modulus - 1;
			}
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
			template<typename Sseq>
			static SPROUT_CXX14_CONSTEXPR result_type init_seed(Sseq& seq) {
				return init_seed(sprout::random::detail::seed_one_int<result_type, modulus>(seq));
			}
			template<typename Sseq>
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
			SPROUT_CONSTEXPR inversive_congruential_engine(result_type x, private_construct_t)
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
			explicit SPROUT_CONSTEXPR inversive_congruential_engine(result_type x0)
				: x_(init_seed(x0))
			{}
			template<typename Sseq>
			explicit SPROUT_CXX14_CONSTEXPR inversive_congruential_engine(Sseq& seq)
				: x_(init_seed(seq))
			{}
			template<typename Sseq>
			explicit SPROUT_CONSTEXPR inversive_congruential_engine(Sseq const& seq)
				: x_(init_seed(seq))
			{}
			template<typename InputIterator>
			SPROUT_CONSTEXPR inversive_congruential_engine(InputIterator first, InputIterator last)
				: x_(init_seed(first, last))
			{}
			SPROUT_CXX14_CONSTEXPR void seed(result_type x0 = default_seed) {
				x_ = init_seed(x0);
			}
			template<typename Sseq>
			SPROUT_CXX14_CONSTEXPR void seed(Sseq& seq) {
				x_ = init_seed(seq);
			}
			template<typename Sseq>
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
				typedef sprout::random::detail::const_mod<result_type, p> do_mod;
				x_ = do_mod::mult_add(a, do_mod::invert(x_), b);
				return x_;
			}
			SPROUT_CONSTEXPR sprout::random::random_result<inversive_congruential_engine> const operator()() const {
				typedef sprout::random::detail::const_mod<result_type, p> do_mod;
				return generate(do_mod::mult_add(a, do_mod::invert(x_), b));
			}
			friend SPROUT_CONSTEXPR bool operator==(inversive_congruential_engine const& lhs, inversive_congruential_engine const& rhs) SPROUT_NOEXCEPT {
				return lhs.x_ == rhs.x_;
			}
			friend SPROUT_CONSTEXPR bool operator!=(inversive_congruential_engine const& lhs, inversive_congruential_engine const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				inversive_congruential_engine& rhs
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
		typedef sprout::random::inversive_congruential_engine<std::uint_fast32_t, 9102, 2147483647 - 36884165, 2147483647> hellekalek1995;
	}	// namespace random

	using sprout::random::inversive_congruential_engine;
	using sprout::random::hellekalek1995;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_INVERSIVE_CONGRUENTIAL_HPP

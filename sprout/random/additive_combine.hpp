/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_ADDITIVE_COMBINE_HPP
#define SPROUT_RANDOM_ADDITIVE_COMBINE_HPP

#include <cstdint>
#include <istream>
#include <ostream>
#include <sprout/config.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/linear_congruential.hpp>
#include <sprout/random/type_traits.hpp>
#include <sprout/random/results.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace random {
		//
		// additive_combine_engine
		//
		template<typename MLCG1, typename MLCG2>
		class additive_combine_engine {
		public:
			typedef MLCG1 base1_type;
			typedef MLCG2 base2_type;
			typedef base1_type first_base;
			typedef base2_type second_base;
			typedef typename base1_type::result_type result_type;
		private:
			static SPROUT_CONSTEXPR result_type static_min() SPROUT_NOEXCEPT {
				return 1;
			}
			static SPROUT_CONSTEXPR result_type static_max() SPROUT_NOEXCEPT {
				return base1_type::modulus - 1;
			}
		public:
			struct private_construct_t {};
		private:
			base1_type mlcg1_;
			base2_type mlcg2_;
		private:
			SPROUT_CONSTEXPR additive_combine_engine(
				base1_type const& mlcg1, base2_type const& mlcg2,
				private_construct_t
				)
				: mlcg1_(mlcg1), mlcg2_(mlcg2)
			{}
			template<typename Random1, typename Random2>
			SPROUT_CONSTEXPR sprout::random::random_result<additive_combine_engine> generate(Random1 const& rnd1, Random2 const& rnd2) const {
				return sprout::random::random_result<additive_combine_engine>(
					sprout::random::result(rnd2) < sprout::random::result(rnd1)
						? sprout::random::result(rnd1) - sprout::random::result(rnd2)
						: sprout::random::result(rnd1) - sprout::random::result(rnd2) + base1_type::modulus - 1
						,
					additive_combine_engine(
						sprout::random::next(rnd1), sprout::random::next(rnd2),
						private_construct_t()
						)
					);
			}
		public:
			SPROUT_CONSTEXPR additive_combine_engine()
				: mlcg1_(), mlcg2_()
			{}
			additive_combine_engine(additive_combine_engine const&) = default;
			explicit SPROUT_CONSTEXPR additive_combine_engine(result_type seed)
				: mlcg1_(seed), mlcg2_(seed)
			{}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			explicit SPROUT_CXX14_CONSTEXPR additive_combine_engine(Sseq& seq)
				: mlcg1_(seq), mlcg2_(seq)
			{}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			explicit SPROUT_CONSTEXPR additive_combine_engine(Sseq const& seq)
				: mlcg1_(seq), mlcg2_(seq)
			{}
			template<typename ForwardIterator>
			SPROUT_CONSTEXPR additive_combine_engine(ForwardIterator first, ForwardIterator last)
				: mlcg1_(first, last), mlcg2_(first, last)
			{}
			SPROUT_CONSTEXPR additive_combine_engine(typename base1_type::result_type seed1, typename base2_type::result_type seed2)
				: mlcg1_(seed1), mlcg2_(seed2)
			{}
			SPROUT_CONSTEXPR additive_combine_engine(base1_type const& rng1, base2_type const& rng2)
				: mlcg1_(rng1), mlcg2_(rng2)
			{}
			SPROUT_CXX14_CONSTEXPR void seed() {
				mlcg1_.seed();
				mlcg2_.seed();
			}
			SPROUT_CXX14_CONSTEXPR void seed(result_type seed) {
				mlcg1_.seed(seed);
				mlcg2_.seed(seed);
			}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			SPROUT_CXX14_CONSTEXPR void seed(Sseq& seq) {
				mlcg1_.seed(seq);
				mlcg2_.seed(seq);
			}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			SPROUT_CXX14_CONSTEXPR void seed(Sseq const& seq) {
				mlcg1_.seed(seq);
				mlcg2_.seed(seq);
			}
			template<typename ForwardIterator>
			SPROUT_CXX14_CONSTEXPR void seed(ForwardIterator first, ForwardIterator last) {
				mlcg1_.seed(first, last);
				mlcg2_.seed(first, last);
			}
			SPROUT_CXX14_CONSTEXPR void seed(typename base1_type::result_type seed1, typename base2_type::result_type seed2) {
				mlcg1_.seed(seed1);
				mlcg2_.seed(seed2);
			}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return 1;
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return base1_type::modulus - 1;
			}
			SPROUT_CXX14_CONSTEXPR result_type operator()() {
				result_type val1 = static_cast<result_type>(mlcg1_());
				result_type val2 = static_cast<result_type>(mlcg2_());
				return val2 < val1
					? val1 - val2
					: val1 - val2 + base1_type::modulus - 1
					;
			}
			SPROUT_CONSTEXPR sprout::random::random_result<additive_combine_engine> const operator()() const {
				return generate(mlcg1_(), mlcg2_());
			}
			SPROUT_CONSTEXPR base1_type const& base1() const SPROUT_NOEXCEPT {
				return mlcg1_;
			}
			SPROUT_CONSTEXPR base2_type const& base2() const SPROUT_NOEXCEPT {
				return mlcg2_;
			}
			friend SPROUT_CONSTEXPR bool operator==(additive_combine_engine const& lhs, additive_combine_engine const& rhs) SPROUT_NOEXCEPT {
				return lhs.mlcg1_ == rhs.mlcg1_ && lhs.mlcg2_ == rhs.mlcg2_;
			}
			friend SPROUT_CONSTEXPR bool operator!=(additive_combine_engine const& lhs, additive_combine_engine const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				additive_combine_engine& rhs
				)
			{
				return lhs >> rhs.mlcg1_ >> std::ws >> rhs.mlcg2_;
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				additive_combine_engine const& rhs
				)
			{
				return lhs << rhs.mlcg1_ << ' ' << rhs.mlcg2_;
			}
		};

		//
		// ecuyer1988
		//
		typedef sprout::random::additive_combine_engine<
			sprout::random::linear_congruential_engine<std::uint_fast32_t, 40014, 0, 2147483563>,
			sprout::random::linear_congruential_engine<std::uint_fast32_t, 40692, 0, 2147483399>
		> ecuyer1988;
	}	// namespace random

	using sprout::random::additive_combine_engine;
	using sprout::random::ecuyer1988;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_ADDITIVE_COMBINE_HPP

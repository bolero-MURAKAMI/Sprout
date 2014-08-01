/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_XOR_COMBINE_HPP
#define SPROUT_RANDOM_XOR_COMBINE_HPP

#include <ios>
#include <istream>
#include <sprout/config.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/type_traits.hpp>
#include <sprout/random/results.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace random {
		//
		// xor_combine_engine
		//
		template<typename URNG1, int s1, typename URNG2, int s2>
		class xor_combine_engine {
		public:
			typedef URNG1 base1_type;
			typedef URNG2 base2_type;
			typedef base1_type first_base;
			typedef base2_type second_base;
			typedef typename base1_type::result_type result_type;
		public:
			SPROUT_STATIC_CONSTEXPR int shift1 = s1;
			SPROUT_STATIC_CONSTEXPR int shift2 = s2;
		public:
			static SPROUT_CONSTEXPR result_type static_min() SPROUT_NOEXCEPT {
				return NS_SSCRISK_CEL_OR_SPROUT::min(base1_type::static_min(), base2_type::static_min());
			}
			static SPROUT_CONSTEXPR result_type static_max() SPROUT_NOEXCEPT {
				return NS_SSCRISK_CEL_OR_SPROUT::max(base1_type::static_max(), base2_type::static_max());
			}
		private:
			base1_type rng1_;
			base2_type rng2_;
		private:
			template<typename EngineResult1, typename EngineResult2>
			SPROUT_CONSTEXPR sprout::random::random_result<xor_combine_engine> generate(EngineResult1 const& rnd1, EngineResult2 const& rnd2) const {
				return sprout::random::random_result<xor_combine_engine>(
					(sprout::random::result(rnd1) << s1) ^ (sprout::random::result(rnd2) << s2),
					xor_combine_engine(
						sprout::random::next(rnd1), sprout::random::next(rnd2)
						)
					);
			}
		public:
			SPROUT_CONSTEXPR xor_combine_engine()
				: rng1_(), rng2_()
			{}
			xor_combine_engine(xor_combine_engine const&) = default;
			explicit SPROUT_CONSTEXPR xor_combine_engine(result_type seed)
				: rng1_(seed), rng2_(seed)
			{}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			explicit SPROUT_CXX14_CONSTEXPR xor_combine_engine(Sseq& seq)
				: rng1_(seq), rng2_(seq)
			{}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			explicit SPROUT_CONSTEXPR xor_combine_engine(Sseq const& seq)
				: rng1_(seq), rng2_(seq)
			{}
			template<typename ForwardIterator>
			SPROUT_CONSTEXPR xor_combine_engine(ForwardIterator first, ForwardIterator last)
				: rng1_(first, last), rng2_(first, last)
			{}
			SPROUT_CONSTEXPR xor_combine_engine(typename base1_type::result_type seed1, typename base2_type::result_type seed2)
				: rng1_(seed1), rng2_(seed2)
			{}
			SPROUT_CONSTEXPR xor_combine_engine(base1_type const& rng1, base2_type const& rng2)
				: rng1_(rng1), rng2_(rng2)
			{}
			SPROUT_CXX14_CONSTEXPR void seed() {
				rng1_.seed();
				rng2_.seed();
			}
			SPROUT_CXX14_CONSTEXPR void seed(result_type seed) {
				rng1_.seed(seed);
				rng2_.seed(seed);
			}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			SPROUT_CXX14_CONSTEXPR void seed(Sseq& seq) {
				rng1_.seed(seq);
				rng2_.seed(seq);
			}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			SPROUT_CXX14_CONSTEXPR void seed(Sseq const& seq) {
				rng1_.seed(seq);
				rng2_.seed(seq);
			}
			template<typename ForwardIterator>
			SPROUT_CXX14_CONSTEXPR void seed(ForwardIterator first, ForwardIterator last) {
				rng1_.seed(first, last);
				rng2_.seed(first, last);
			}
			SPROUT_CXX14_CONSTEXPR void seed(typename base1_type::result_type seed1, typename base2_type::result_type seed2) {
				rng1_.seed(seed1);
				rng2_.seed(seed2);
			}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return NS_SSCRISK_CEL_OR_SPROUT::min(rng1_.min(), rng2_.min());
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return NS_SSCRISK_CEL_OR_SPROUT::max(rng1_.max(), rng2_.max());
			}
			SPROUT_CXX14_CONSTEXPR result_type operator()() {
				return (static_cast<result_type>(rng1_()) << s1) ^ (static_cast<result_type>(rng2_()) << s2);
			}
			SPROUT_CONSTEXPR sprout::random::random_result<xor_combine_engine> const operator()() const {
				return generate(rng1_(), rng2_());
			}
			SPROUT_CONSTEXPR base1_type const& base1() const SPROUT_NOEXCEPT {
				return rng1_;
			}
			SPROUT_CONSTEXPR base2_type const& base2() const SPROUT_NOEXCEPT {
				return rng2_;
			}
			friend SPROUT_CONSTEXPR bool operator==(xor_combine_engine const& lhs, xor_combine_engine const& rhs) SPROUT_NOEXCEPT {
				return lhs.rng1_ == rhs.rng1_ && lhs.rng2_ == rhs.rng2_;
			}
			friend SPROUT_CONSTEXPR bool operator!=(xor_combine_engine const& lhs, xor_combine_engine const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				xor_combine_engine& rhs
				)
			{
				return lhs >> rhs.rng1_ >> std::ws >> rhs.rng2_;
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				xor_combine_engine const& rhs
				)
			{
				return lhs << rhs.rng1_ << ' ' << rhs.rng2_;
			}
		};
		template<typename URNG1, int s1, typename URNG2, int s2>
		SPROUT_CONSTEXPR_OR_CONST int sprout::random::xor_combine_engine<URNG1, s1, URNG2, s2>::shift1;
		template<typename URNG1, int s1, typename URNG2, int s2>
		SPROUT_CONSTEXPR_OR_CONST int sprout::random::xor_combine_engine<URNG1, s1, URNG2, s2>::shift2;
	}	// namespace random

	using sprout::random::xor_combine_engine;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_XOR_COMBINE_HPP

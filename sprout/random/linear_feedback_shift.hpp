/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_LINEAR_FEEDBACK_SHIFT_HPP
#define SPROUT_RANDOM_LINEAR_FEEDBACK_SHIFT_HPP

#include <istream>
#include <ostream>
#include <sprout/config.hpp>
#include <sprout/detail/integer/integer_mask.hpp>
#include <sprout/random/detail/seed_impl.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/type_traits.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace random {
		//
		// linear_feedback_shift_engine
		//
		template<typename UIntType, int w, int k, int q, int s>
		class linear_feedback_shift_engine {
		public:
			typedef UIntType result_type;
		private:
			struct private_construct_t {};
		public:
			SPROUT_STATIC_CONSTEXPR int word_size = w;
			SPROUT_STATIC_CONSTEXPR int exponent1 = k;
			SPROUT_STATIC_CONSTEXPR int exponent2 = q;
			SPROUT_STATIC_CONSTEXPR int step_size = s;
			SPROUT_STATIC_CONSTEXPR result_type default_seed = 341;
		public:
			static_assert(w > 0, "w > 0");
			static_assert(q > 0, "q > 0");
			static_assert(k < w, "k < w");
			static_assert(0 < 2 * q && 2 * q < k, "0 < 2 * q && 2 * q < k");
			static_assert(0 < s && s <= k - q, "0 < s && s <= k - q");
		public:
			static SPROUT_CONSTEXPR result_type static_min() SPROUT_NOEXCEPT {
				return 0;
			}
			static SPROUT_CONSTEXPR result_type static_max() SPROUT_NOEXCEPT {
				return wordmask();
			}
		private:
			static SPROUT_CONSTEXPR result_type wordmask() {
				return sprout::detail::low_bits_mask_t<w>::sig_bits;
			}
			static SPROUT_CONSTEXPR result_type init_seed_1(result_type x0) {
				return x0 < (1 << (w - k)) ? x0 + (1 << (w - k)) : x0;
			}
			static SPROUT_CONSTEXPR result_type init_seed(result_type x0 = default_seed) {
				return init_seed_1(x0 & wordmask());
			}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			static SPROUT_CXX14_CONSTEXPR result_type init_seed(Sseq& seq) {
				return init_seed(sprout::random::detail::seed_one_int<result_type, (result_type(2) << (w - 1))>(seq));
			}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			static SPROUT_CONSTEXPR result_type init_seed(Sseq const& seq) {
				return init_seed(sprout::random::detail::seed_one_int<result_type, (result_type(2) << (w - 1))>(seq));
			}
			template<typename InputIterator>
			static SPROUT_CONSTEXPR result_type init_seed(InputIterator first, InputIterator last) {
				return init_seed(sprout::random::detail::get_one_int<result_type, (result_type(2) << (w - 1))>(first, last));
			}
		private:
			result_type x_;
		private:
			SPROUT_CONSTEXPR linear_feedback_shift_engine(result_type x, private_construct_t)
				: x_(x)
			{}
			SPROUT_CONSTEXPR sprout::random::random_result<linear_feedback_shift_engine> generate(result_type result) const {
				return sprout::random::random_result<linear_feedback_shift_engine>(
					result,
					linear_feedback_shift_engine(result, private_construct_t())
					);
			}
		public:
			SPROUT_CONSTEXPR linear_feedback_shift_engine()
				: x_(init_seed(default_seed))
			{}
			linear_feedback_shift_engine(linear_feedback_shift_engine const&) = default;
			explicit SPROUT_CONSTEXPR linear_feedback_shift_engine(result_type x0)
				: x_(init_seed(x0))
			{}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			explicit SPROUT_CXX14_CONSTEXPR linear_feedback_shift_engine(Sseq& seq)
				: x_(init_seed(seq))
			{}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			explicit SPROUT_CONSTEXPR linear_feedback_shift_engine(Sseq const& seq)
				: x_(init_seed(seq))
			{}
			template<typename InputIterator>
			SPROUT_CONSTEXPR linear_feedback_shift_engine(InputIterator first, InputIterator last)
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
				 x_ = ((x_ & ((wordmask() << (w - k)) & wordmask())) << s) ^ ((((x_ << q) ^ x_) & wordmask()) >> (k - s));
				 return x_;
			}
			SPROUT_CONSTEXPR sprout::random::random_result<linear_feedback_shift_engine> const operator()() const {
				return generate(((x_ & ((wordmask() << (w - k)) & wordmask())) << s) ^ ((((x_ << q) ^ x_) & wordmask()) >> (k - s)));
			}
			friend SPROUT_CONSTEXPR bool operator==(linear_feedback_shift_engine const& lhs, linear_feedback_shift_engine const& rhs) SPROUT_NOEXCEPT {
				return lhs.x_ == rhs.x_;
			}
			friend SPROUT_CONSTEXPR bool operator!=(linear_feedback_shift_engine const& lhs, linear_feedback_shift_engine const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				linear_feedback_shift_engine& rhs
				)
			{
				return lhs >> rhs.x_;
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				linear_feedback_shift_engine const& rhs
				)
			{
				return lhs << rhs.x_;
			}
		};
		template<typename UIntType, int w, int k, int q, int s>
		SPROUT_CONSTEXPR_OR_CONST int sprout::random::linear_feedback_shift_engine<UIntType, w, k, q, s>::word_size;
		template<typename UIntType, int w, int k, int q, int s>
		SPROUT_CONSTEXPR_OR_CONST int sprout::random::linear_feedback_shift_engine<UIntType, w, k, q, s>::exponent1;
		template<typename UIntType, int w, int k, int q, int s>
		SPROUT_CONSTEXPR_OR_CONST int sprout::random::linear_feedback_shift_engine<UIntType, w, k, q, s>::exponent2;
		template<typename UIntType, int w, int k, int q, int s>
		SPROUT_CONSTEXPR_OR_CONST int sprout::random::linear_feedback_shift_engine<UIntType, w, k, q, s>::step_size;
		template<typename UIntType, int w, int k, int q, int s>
		SPROUT_CONSTEXPR_OR_CONST UIntType sprout::random::linear_feedback_shift_engine<UIntType, w, k, q, s>::default_seed;
	}	// namespace random

	using sprout::random::linear_feedback_shift_engine;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_LINEAR_FEEDBACK_SHIFT_HPP

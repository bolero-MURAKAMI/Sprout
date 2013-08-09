/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_LINEAR_FEEDBACK_SHIFT_HPP
#define SPROUT_RANDOM_LINEAR_FEEDBACK_SHIFT_HPP

#include <ios>
#include <sprout/config.hpp>
#include <sprout/detail/integer/integer_mask.hpp>
#include <sprout/random/random_result.hpp>

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
			SPROUT_STATIC_CONSTEXPR UIntType default_seed = 341;
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
			static SPROUT_CONSTEXPR UIntType wordmask() {
				return sprout::detail::low_bits_mask_t<w>::sig_bits;
			}
			static SPROUT_CONSTEXPR UIntType init_seed_1(UIntType const& x0) {
				return x0 < (1 << (w - k)) ? x0 + (1 << (w - k)) : x0;
			}
			static SPROUT_CONSTEXPR UIntType init_seed(UIntType const& x0) {
				return init_seed_1(x0 & wordmask());
			}
		private:
			UIntType x_;
		private:
			SPROUT_CONSTEXPR linear_feedback_shift_engine(UIntType const& x, private_construct_t)
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
			explicit SPROUT_CONSTEXPR linear_feedback_shift_engine(UIntType const& x0)
				: x_(init_seed(x0))
			{}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return static_min();
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return static_max();
			}
			SPROUT_CONSTEXPR sprout::random::random_result<linear_feedback_shift_engine> operator()() const {
				return generate(((x_ & ((wordmask() << (w - k)) & wordmask())) << s) ^ ((((x_ << q) ^ x_) & wordmask()) >> (k - s)));
			}
			friend SPROUT_CONSTEXPR bool operator==(linear_feedback_shift_engine const& lhs, linear_feedback_shift_engine const& rhs) SPROUT_NOEXCEPT {
				return lhs.x_ == rhs.x_;
			}
			friend SPROUT_CONSTEXPR bool operator!=(linear_feedback_shift_engine const& lhs, linear_feedback_shift_engine const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
			template<typename Elem, typename Traits>
			friend std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				linear_feedback_shift_engine& rhs
				)
			{
				return lhs >> rhs.x_;
			}
			template<typename Elem, typename Traits>
			friend std::basic_ostream<Elem, Traits>& operator<<(
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

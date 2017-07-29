/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_HASH_DETAIL_HASH_FLOAT_HPP
#define SPROUT_FUNCTIONAL_HASH_DETAIL_HASH_FLOAT_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>
#include <sprout/math/fpclassify.hpp>
#include <sprout/math/ldexp.hpp>
#include <sprout/math/float2_sig_exp.hpp>
#include <sprout/detail/integer/static_log2.hpp>

namespace sprout {
	namespace detail {
		inline SPROUT_CONSTEXPR std::size_t
		hash_float_combine(std::size_t seed, std::size_t value) {
			return seed ^ (value + (seed << 6) + (seed >> 2));
		}

		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		float_hash_value_impl_4(T v, int exp, std::size_t seed, std::size_t length, std::size_t i = 0) {
			return i != length ? sprout::detail::float_hash_value_impl_4(
					sprout::ldexp(v - static_cast<T>(static_cast<std::size_t>(v)), sprout::numeric_limits<std::size_t>::digits),
					exp, sprout::detail::hash_float_combine(seed, static_cast<std::size_t>(v)),
					length, i + 1
					)
				: sprout::detail::hash_float_combine(seed, exp)
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		float_hash_value_impl_3(T v, int exp) {
			return sprout::detail::float_hash_value_impl_4(
				sprout::ldexp(v - static_cast<T>(static_cast<std::size_t>(v)), sprout::numeric_limits<std::size_t>::digits),
				exp, static_cast<std::size_t>(v),
				(sprout::numeric_limits<T>::digits * sprout::detail::static_log2<sprout::numeric_limits<T>::radix>::value + sprout::numeric_limits<std::size_t>::digits - 1)
					/ sprout::numeric_limits<std::size_t>::digits
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		float_hash_value_impl_2(T v, int exp) {
			return sprout::detail::float_hash_value_impl_3(sprout::ldexp(v, sprout::numeric_limits<std::size_t>::digits), exp);
		}
		template<typename T, typename P>
		inline SPROUT_CONSTEXPR std::size_t
		float_hash_value_impl_1(P const& p) {
			return ((p.first) < 0) ? sprout::detail::float_hash_value_impl_2(
					-p.first, p.second + (sprout::numeric_limits<T>::max_exponent - sprout::numeric_limits<T>::min_exponent)
					)
				: sprout::detail::float_hash_value_impl_2(p.first, p.second)
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		float_hash_value_impl(T v) {
			return sprout::detail::float_hash_value_impl_1<T>(sprout::math::float2_sig_exp(v));
		}

		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		float_hash_value_1(T v, int fp) {
			return fp == FP_ZERO ? 0
				: fp == FP_INFINITE ? std::size_t(v > 0 ? -1 : -2)
				: fp == FP_NAN ? std::size_t(-3)
				: sprout::detail::float_hash_value_impl(v)
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		float_hash_value(T v) {
			return sprout::detail::float_hash_value_1(v, sprout::fpclassify(v));
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_DETAIL_HASH_FLOAT_HPP

/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_PARAM_AT_HPP
#define SPROUT_DETAIL_PARAM_AT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>

namespace sprout {
	namespace detail {
		template<typename R, typename T, typename... Values>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sizeof...(Values) == 0,
			R
		>::type
		param_at(std::size_t, T const& v, Values const&...) {
			return v;
		}
		template<typename R, typename T, typename... Values>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sizeof...(Values) != 0,
			R
		>::type
		param_at(std::size_t n, T const& v, Values const&... values) {
			return n == 0 ? v : sprout::detail::param_at<R>(n - 1, values...);
		}

		template<typename R, typename T, typename... Values>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sizeof...(Values) == 0,
			R
		>::type
		param_seq_at(std::size_t, std::size_t m, T const& v, Values const&...) {
			return v[m];
		}
		template<typename R, typename T, typename... Values>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sizeof...(Values) != 0,
			R
		>::type
		param_seq_at(std::size_t n, std::size_t m, T const& v, Values const&... values) {
			return n == 0 ? v[m] : sprout::detail::param_seq_at<R>(n - 1, m, values...);
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_PARAM_AT_HPP

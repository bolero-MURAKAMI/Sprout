/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_INTEGER_STATIC_LOG2_HPP
#define SPROUT_DETAIL_INTEGER_STATIC_LOG2_HPP

#include <cstdint>
#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		typedef std::uintmax_t static_log2_argument_type;
		typedef int static_log2_result_type;

		namespace static_log2_impl {
			typedef sprout::detail::static_log2_argument_type argument_type;
			typedef sprout::detail::static_log2_result_type result_type;

			template<result_type n>
			struct choose_initial_n {
				SPROUT_STATIC_CONSTEXPR bool c
					= (sprout::detail::static_log2_impl::argument_type(1) << n << n) != 0
					;
				SPROUT_STATIC_CONSTEXPR sprout::detail::static_log2_impl::result_type value
					= !c * n + choose_initial_n<2 * c * n>::value
					;
			};
			template<>
			struct choose_initial_n<0> {
				SPROUT_STATIC_CONSTEXPR sprout::detail::static_log2_impl::result_type value = 0;
			};

			SPROUT_STATIC_CONSTEXPR sprout::detail::static_log2_impl::result_type n_zero = 16;
			SPROUT_STATIC_CONSTEXPR sprout::detail::static_log2_impl::result_type initial_n
				= sprout::detail::static_log2_impl::choose_initial_n<n_zero>::value
				;

			template<
				sprout::detail::static_log2_impl::argument_type x,
				sprout::detail::static_log2_impl::result_type n = sprout::detail::static_log2_impl::initial_n
			>
			struct static_log2_impl {
				SPROUT_STATIC_CONSTEXPR bool c = (x >> n) > 0;
				SPROUT_STATIC_CONSTEXPR sprout::detail::static_log2_impl::result_type value
					= c * n + (static_log2_impl<(x >> c * n), n / 2>::value)
					;
			};
			template<>
			struct static_log2_impl<1, 0> {
				SPROUT_STATIC_CONSTEXPR sprout::detail::static_log2_impl::result_type value = 0;
			};
		}	// namespace static_log2_impl

		template<sprout::detail::static_log2_argument_type x>
		struct static_log2 {
			SPROUT_STATIC_CONSTEXPR sprout::detail::static_log2_result_type value
				= sprout::detail::static_log2_impl::static_log2_impl<x>::value
				;
		};
		template<>
		struct static_log2<0> {};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_INTEGER_STATIC_LOG2_HPP

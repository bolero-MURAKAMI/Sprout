/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_STATIC_SIZE_HPP
#define SPROUT_DETAIL_STATIC_SIZE_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		template<typename T, T V>
		struct base_static_size {
		public:
			SPROUT_STATIC_CONSTEXPR T static_size = V;
		public:
			static SPROUT_CONSTEXPR T
			fixed_size() SPROUT_NOEXCEPT {
				return static_size;
			}
		};
		template<typename T, T V>
		SPROUT_CONSTEXPR_OR_CONST T sprout::detail::base_static_size<T, V>::static_size;

		template<typename Container>
		struct inherit_static_size
			: public sprout::detail::base_static_size<typename Container::size_type, Container::static_size>
		{};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_STATIC_SIZE_HPP

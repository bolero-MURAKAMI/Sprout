/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_DETAIL_TYPE_TRAITS_WRAPPER_HPP
#define SPROUT_TYPE_TRAITS_DETAIL_TYPE_TRAITS_WRAPPER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace detail {
		//
		// type_traits_wrapper
		//
		template<typename T>
		struct type_traits_wrapper
			: public sprout::integral_constant<typename T::value_type, T::value>
		{};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_DETAIL_TYPE_TRAITS_WRAPPER_HPP

/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_CONST_UNQUALIFIED_HPP
#define SPROUT_TYPE_TRAITS_IS_CONST_UNQUALIFIED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_const_unqualified
	//
	template<typename T>
	struct is_const_unqualified
		: public sprout::integral_constant<
			bool,
			std::is_const<T>::value
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_CONST_UNQUALIFIED_HPP

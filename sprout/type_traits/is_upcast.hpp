/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_UPCAST_HPP
#define SPROUT_TYPE_TRAITS_IS_UPCAST_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/std_type_traits.hpp>
#include <sprout/type_traits/is_nullptr_cast.hpp>

namespace sprout {
	//
	// is_upcast
	//
	template<typename From, typename To>
	struct is_upcast
		: public sprout::bool_constant<
			sprout::is_nullptr_cast<From, To>::value
				|| (sprout::is_pointer<To>::value
					&& sprout::is_base_of<typename sprout::remove_pointer<To>::type, typename sprout::remove_pointer<typename sprout::decay<From>::type>::type>::value
					)
				|| (sprout::is_reference<To>::value
					&& sprout::is_base_of<typename sprout::remove_reference<To>::type, typename sprout::remove_reference<From>::type>::value
					)
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_UPCAST_HPP

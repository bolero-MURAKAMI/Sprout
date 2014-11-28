/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_NULLPTR_CAST_HPP
#define SPROUT_TYPE_TRAITS_IS_NULLPTR_CAST_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/std_type_traits.hpp>

namespace sprout {
	//
	// is_nullptr_cast
	//
	template<typename From, typename To>
	struct is_nullptr_cast
		: public sprout::integral_constant<
			bool,
			sprout::is_pointer<To>::value && sprout::is_same<typename sprout::decay<From>::type, std::nullptr_t>::value
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_NULLPTR_CAST_HPP

/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VARIANT_TYPE_TRAITS_HPP
#define SPROUT_VARIANT_TYPE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/variant/variant_fwd.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_variant
	//
	template<typename T>
	struct is_variant
		: public sprout::false_type
	{};
	template<typename T>
	struct is_variant<T const>
		: public sprout::is_variant<T>
	{};
	template<typename T>
	struct is_variant<T const volatile>
		: public sprout::is_variant<T>
	{};
	template<typename... Types>
	struct is_variant<sprout::variant<Types...> >
		: public sprout::true_type
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_TYPE_TRAITS_HPP

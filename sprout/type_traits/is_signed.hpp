/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_SIGNED_HPP
#define SPROUT_TYPE_TRAITS_IS_SIGNED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>

namespace sprout {
	//
	// is_signed
	//
	namespace detail {
		template<typename T, bool = std::is_arithmetic<T>::value>
		struct is_signed_impl
			: public sprout::false_type
		{};
		template<typename T>
		struct is_signed_impl<T, true>
			: public sprout::detail::type_traits_wrapper<std::is_signed<T> >
		{};
	}	// namespace detail
	template <typename T>
	struct is_signed
		: public sprout::detail::is_signed_impl<T>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_SIGNED_HPP

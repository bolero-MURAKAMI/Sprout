/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_CONVERT_CONSTRUCTIBLE_HPP
#define SPROUT_TYPE_TRAITS_IS_CONVERT_CONSTRUCTIBLE_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_convert_constructible
	//
	namespace detail {
		template<typename T>
		struct is_convert_constructible_test {
		public:
			static sprout::true_type test(T);
			static sprout::false_type test(...);
		};
	}	// namespace detail
	template<typename T, typename Arg>
	struct is_convert_constructible
		: public sprout::identity<decltype(sprout::detail::is_convert_constructible_test<T>::test(std::declval<Arg>()))>::type
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T, typename Arg>
	SPROUT_STATIC_CONSTEXPR bool is_convert_constructible_v = sprout::is_convert_constructible<T, Arg>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_CONVERT_CONSTRUCTIBLE_HPP

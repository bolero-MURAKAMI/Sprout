/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_CONST_CAST_CONVERTIBLE_HPP
#define SPROUT_TYPE_TRAITS_IS_CONST_CAST_CONVERTIBLE_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_const_cast_convertible
	//
	namespace detail {
		template<typename From, typename To>
		struct is_const_cast_convertible_test {
		public:
			template<
				typename FromU = From,
				typename = typename sprout::identity<decltype(const_cast<To>(std::declval<FromU>()))>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
	}	// namespace detail
	template<typename From, typename To>
	struct is_const_cast_convertible
		: public sprout::identity<decltype(sprout::detail::is_const_cast_convertible_test<From, To>::test(0))>::type
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename From, typename To>
	SPROUT_STATIC_CONSTEXPR bool is_const_cast_convertible_v = sprout::is_const_cast_convertible<From, To>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_CONST_CAST_CONVERTIBLE_HPP

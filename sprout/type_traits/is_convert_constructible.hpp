/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_CONVERT_CONSTRUCTIBLE_HPP
#define SPROUT_TYPE_TRAITS_IS_CONVERT_CONSTRUCTIBLE_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_convert_constructible
	//
	namespace detail {
		template<typename T>
		struct is_convert_constructible_test {
		public:
			template<typename To = T>
			static sprout::true_type test(To);
			static sprout::false_type test(...);
		};
	}	// namespace detail
	template<typename T, typename Arg>
	struct is_convert_constructible
		: public decltype(sprout::detail::is_convert_constructible_test<T>::test(std::declval<Arg>()))
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename Arg>
	using is_convert_constructible_t = typename sprout::is_convert_constructible<T, Arg>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_CONVERT_CONSTRUCTIBLE_HPP

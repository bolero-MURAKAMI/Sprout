/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP
#define SPROUT_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout_swappable_detail {
	using std::swap;

	template<typename T, typename U>
	struct is_swappable_with_test {
	public:
		template<
			typename T1 = T, typename U1 = U,
			typename = typename sprout::identity<decltype(swap(std::declval<T1>(), std::declval<U1>()))>::type,
			typename = typename sprout::identity<decltype(swap(std::declval<U1>(), std::declval<T1>()))>::type
		>
		static sprout::true_type test(int);
		static sprout::false_type test(...);
	};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
	template<typename T, typename U, typename Base_ = typename sprout::identity<decltype(sprout_swappable_detail::is_swappable_with_test<T, U>::test(0))>::type>
	struct is_swappable_with
		: public Base_
	{};
#else
	template<typename T, typename U>
	struct is_swappable_with
		: public sprout::identity<decltype(sprout_swappable_detail::is_swappable_with_test<T, U>::test(0))>::type
	{};
#endif
}	// namespace sprout_swappable_detail

namespace sprout {
	//
	// is_swappable_with
	//
	template<typename T, typename U>
	struct is_swappable_with
		: public sprout_swappable_detail::is_swappable_with<T, U>
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T, typename U>
	SPROUT_STATIC_CONSTEXPR bool is_swappable_with_v = sprout::is_swappable_with<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP

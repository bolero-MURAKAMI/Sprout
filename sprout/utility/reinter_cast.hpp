/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_REINTER_CAST_HPP
#define SPROUT_UTILITY_REINTER_CAST_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace detail {
		template<typename From, typename To>
		struct is_same_reinterpret_cast
			: public sprout::bool_constant<
				(std::is_reference<To>::value
					&& std::is_same<typename std::decay<From>::type, typename std::decay<To>::type>::value
					&& std::is_convertible<From, To>::value
					)
					|| ((std::is_integral<To>::type || std::is_enum<To>::type || std::is_pointer<To>::type)
						&& std::is_same<typename std::decay<From>::type, To>::value
						)

			>
		{};
	}	// namespace detail
 	//
	// reinter_cast
	//
	template<
		typename T, typename U,
		typename sprout::enabler_if<sprout::detail::is_same_reinterpret_cast<U&&, T>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR T
	reinter_cast(U&& x) {
		return SPROUT_FORWARD(U, x);
	}
	template<
		typename T, typename U,
		typename sprout::enabler_if<!sprout::detail::is_same_reinterpret_cast<U&&, T>::value>::type = sprout::enabler
	>
	inline SPROUT_NON_CONSTEXPR T
	reinter_cast(U&& x) {
		return reinterpret_cast<T>(SPROUT_FORWARD(U, x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_REINTER_CAST_HPP

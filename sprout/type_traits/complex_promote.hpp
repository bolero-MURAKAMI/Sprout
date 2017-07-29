/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_COMPLEX_PROMOTE_HPP
#define SPROUT_TYPE_TRAITS_COMPLEX_PROMOTE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/complex/type_traits.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/arithmetic_promote.hpp>

namespace sprout {
	namespace detail {
		template<typename T, bool = sprout::is_complex<T>::value>
		struct complex_promote1
			: public sprout::identity<T>
		{};
		template<typename T>
		struct complex_promote1<T, false>
			: public sprout::identity<sprout::complex<typename sprout::float_promote<T>::type> >
		{};

		template<typename T, typename U>
		struct complex_promote2
			: public sprout::identity<sprout::complex<
				typename sprout::arithmetic_promote<
					typename sprout::detail::complex_promote1<T>::type::value_type,
					typename sprout::detail::complex_promote1<U>::type::value_type
				>::type
			>>
		{};

		template<typename... Types>
		struct complex_promote_impl;
		template<typename T, typename U, typename... Tail>
		struct complex_promote_impl<T, U, Tail...>
			: public sprout::detail::complex_promote_impl<
				typename sprout::detail::complex_promote2<T, U>::type,
				Tail...
			>
		{};
		template<typename T>
		struct complex_promote_impl<T>
			: public sprout::detail::complex_promote1<T>
		{};
	}	// namespace detail

	//
	// complex_promote
	//
	template<typename... Types>
	struct complex_promote
		: public sprout::detail::complex_promote_impl<
			typename std::remove_cv<Types>::type...
		>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename... Types>
	using complex_promote_t = typename sprout::complex_promote<Types...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_COMPLEX_PROMOTE_HPP

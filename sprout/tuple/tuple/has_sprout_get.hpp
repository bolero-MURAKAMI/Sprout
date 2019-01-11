/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_HAS_SPROUT_GET_HPP
#define SPROUT_TUPLE_TUPLE_HAS_SPROUT_GET_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	//
	// has_sprout_get
	//
	namespace tuples {
		namespace detail {
			template<typename T, typename std::size_t I>
			struct has_sprout_get_test {
			public:
				template<
					typename U = T,
					typename = typename sprout::identity<decltype(sprout::get<I>(std::declval<U>()))>::type
				>
				static sprout::true_type test(int);
				static sprout::false_type test(...);
			};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
			template<typename T, typename std::size_t I, typename Base_ = typename sprout::identity<decltype(sprout::tuples::detail::has_sprout_get_test<T, I>::test(0))>::type>
			struct has_sprout_get
				: public Base_
			{};
#else
			template<typename T, typename std::size_t I>
			struct has_sprout_get
				: public sprout::identity<decltype(sprout::tuples::detail::has_sprout_get_test<T, I>::test(0))>::type
			{};
#endif
		}	// namespace detail
		template<typename T, typename std::size_t I>
		struct has_sprout_get
			: public sprout::tuples::detail::has_sprout_get<T, I>
		{};

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename T, typename std::size_t I>
		SPROUT_STATIC_CONSTEXPR bool has_sprout_get_v = sprout::tuples::has_sprout_get<T, I>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace tuples

	using sprout::tuples::has_sprout_get;
#if SPROUT_USE_VARIABLE_TEMPLATES
	using sprout::tuples::has_sprout_get_v;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_HAS_SPROUT_GET_HPP

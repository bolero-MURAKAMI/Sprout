/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_TUPLE_SIZE_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_SIZE_HPP

#include <tuple>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>
#include <sprout/type_traits/has_value.hpp>
#include <sprout/detail/nil_base.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_size
		//
		namespace detail {
#if defined(_MSC_VER)
			template<typename T, bool = true>
#else
			template<typename T, bool = sprout::has_value<std::tuple_size<T> >::value>
#endif
			struct tuple_size_default;
			template<typename T>
			struct tuple_size_default<T, false>
				: public sprout::detail::nil_base
			{};
			template<typename T>
			struct tuple_size_default<T, true>
				: public sprout::detail::type_traits_wrapper<std::tuple_size<T> >
			{};
		}	// namespace detail
		template<typename T>
		struct tuple_size
			: public sprout::tuples::detail::tuple_size_default<T>
		{};
		template<typename T>
		struct tuple_size<T const>
			: public sprout::tuples::tuple_size<T>
		{};
		template<typename T>
		struct tuple_size<T volatile>
			: public sprout::tuples::tuple_size<T>
		{};
		template<typename T>
		struct tuple_size<T const volatile>
			: public sprout::tuples::tuple_size<T>
		{};
	}	// namespace tuples

	using sprout::tuples::tuple_size;

#if SPROUT_USE_VARIABLE_TEMPLATES
	namespace tuples {
		template<typename T>
		SPROUT_STATIC_CONSTEXPR std::size_t tuple_size_v = sprout::tuples::tuple_size<T>::value;
	}	// namespace tuples

	using sprout::tuples::tuple_size_v;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_SIZE_HPP

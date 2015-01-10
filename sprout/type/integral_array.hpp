/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_INTEGRAL_ARRAY_HPP
#define SPROUT_TYPE_INTEGRAL_ARRAY_HPP

#include <tuple>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/type_tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace types {
		//
		// integral_array
		//
		template<typename T, T... Values>
		struct integral_array
			: public sprout::types::type_tuple<sprout::integral_constant<T, Values>...>
		{
		public:
			typedef integral_array type;
			typedef T value_type;
		};
	}	// namespace types
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// tuple_size
	//
	template<typename T, T... Values>
	struct tuple_size<sprout::types::integral_array<T, Values...> >
		: public std::tuple_size<sprout::types::type_tuple<sprout::integral_constant<T, Values>...> >
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename T, T... Values>
	struct tuple_element<I, sprout::types::integral_array<T, Values...> >
		: public sprout::types::tuple_element<I, sprout::types::type_tuple<sprout::integral_constant<T, Values>...> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

namespace sprout {
	//
	// tuple_get
	//
	template<std::size_t I, typename T, T... Values>
	inline SPROUT_CONSTEXPR typename std::tuple_element<I, sprout::types::integral_array<T, Values...> >::type
	tuple_get(sprout::types::integral_array<T, Values...>) SPROUT_NOEXCEPT {
		static_assert(I < sizeof...(Values), "tuple_get: index out of range");
		typedef typename std::tuple_element<I, sprout::types::integral_array<T, Values...> >::type type;
		return type();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_INTEGRAL_ARRAY_HPP

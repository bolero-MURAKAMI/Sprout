/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_TUPLE_SIZE_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_SIZE_HPP

#include <tuple>
#include <sprout/config.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_size
		//
		template<typename T>
		struct tuple_size
			: public sprout::detail::type_traits_wrapper<std::tuple_size<T> >
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
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_SIZE_HPP

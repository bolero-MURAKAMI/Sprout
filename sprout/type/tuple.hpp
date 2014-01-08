/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TUPLE_HPP
#define SPROUT_TYPE_TUPLE_HPP

#include <cstddef>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>

namespace sprout {
	namespace types {
		//
		// begin
		//
		template<typename T, typename Enable = void>
		struct begin {
			typedef typename T::begin type;
		};
		//
		// end
		//
		template<typename T, typename Enable = void>
		struct end {
			typedef typename T::end type;
		};

		//
		// tuple_size
		//
		template<typename T, typename Enable = void>
		struct tuple_size
			: public sprout::detail::type_traits_wrapper<std::tuple_size<T> >
		{};
		//
		// tuple_element
		//
		template<std::size_t I, typename T, typename Enable = void>
		struct tuple_element
			: public std::tuple_element<I, T>
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TUPLE_HPP

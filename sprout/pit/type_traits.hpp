/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PIT_TYPE_TRAITS_HPP
#define SPROUT_PIT_TYPE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_pit
	//
	template<typename T>
	struct is_pit
		: public sprout::false_type
	{};
	template<typename T>
	struct is_pit<T const>
		: public sprout::is_pit<T>
	{};
	template<typename T>
	struct is_pit<T const volatile>
		: public sprout::is_pit<T>
	{};
	template<typename Container>
	struct is_pit<sprout::pit<Container> >
		: public sprout::true_type
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_PIT_TYPE_TRAITS_HPP

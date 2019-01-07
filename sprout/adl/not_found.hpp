/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ADL_NOT_FOUND_HPP
#define SPROUT_ADL_NOT_FOUND_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/is_same.hpp>

namespace sprout {
	//
	// not_found_via_adl
	//
	struct not_found_via_adl {};

	//
	// is_not_found_via_adl
	//
	template<typename T>
	struct is_not_found_via_adl
		: public sprout::is_same<T, sprout::not_found_via_adl>
	{};
	template<typename T>
	struct is_not_found_via_adl<T const>
		: public sprout::is_not_found_via_adl<T>
	{};
	template<typename T>
	struct is_not_found_via_adl<T volatile>
		: public sprout::is_not_found_via_adl<T>
	{};
	template<typename T>
	struct is_not_found_via_adl<T const volatile>
		: public sprout::is_not_found_via_adl<T>
	{};

	//
	// is_found_via_adl
	//
	template<typename T>
	struct is_found_via_adl
		: public sprout::bool_constant<!sprout::is_not_found_via_adl<T>::value>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_ADL_NOT_FOUND_HPP

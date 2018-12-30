/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.std.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_WITHIN_NAMESPACE_STD_HPP
#define SPROUT_TYPE_TRAITS_IS_WITHIN_NAMESPACE_STD_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/is_within_tag_namespace.hpp>

//
//	note:
//		This code is ill-formed in the Standard C++
//		because adding declarations to std namespace.
//		However, it will work without problems in practice.
//		I want to replace if there is a better way.
//
namespace std {
	SPROUT_ADL_TESTER_DECL(std);
}	// namespace std

namespace sprout {
	//
	// is_within_namespace_std
	//
	SPROUT_IS_WITHIN_NAMESPACE_DECL(std, std);
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_WITHIN_NAMESPACE_STD_HPP

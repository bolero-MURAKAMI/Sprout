/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_HPP
#define SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/type_traits/has_xxx.hpp>

namespace sprout {
	namespace detail {
		//
		// has_iterator_category
		//
		SPROUT_HAS_XXX_TYPE_DEF_LAZY(iterator_category);
	}	// namespace detail

	//
	// is_iterator
	//
	template<typename T>
	struct is_iterator
		: public sprout::detail::has_iterator_category<std::iterator_traits<T> >
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_iterator_v = sprout::is_iterator<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_HPP

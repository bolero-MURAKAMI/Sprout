/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_CATEGORY_OF_HPP
#define SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_CATEGORY_OF_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// is_iterator_category_of
	//
	template<typename MaybeCategory, typename Category>
	struct is_iterator_category_of
		: public std::is_convertible<MaybeCategory, Category>
	{};

	//
	// is_input_iterator_category
	//
	template<typename MaybeCategory>
	struct is_input_iterator_category
		: public sprout::is_iterator_category_of<MaybeCategory, std::input_iterator_tag>
	{};
	//
	// is_output_iterator_category
	//
	template<typename MaybeCategory>
	struct is_output_iterator_category
		: public sprout::is_iterator_category_of<MaybeCategory, std::output_iterator_tag>
	{};
	//
	// is_forward_iterator_category
	//
	template<typename MaybeCategory>
	struct is_forward_iterator_category
		: public sprout::is_iterator_category_of<MaybeCategory, std::forward_iterator_tag>
	{};
	//
	// is_bidirectional_iterator_category
	//
	template<typename MaybeCategory>
	struct is_bidirectional_iterator_category
		: public sprout::is_iterator_category_of<MaybeCategory, std::bidirectional_iterator_tag>
	{};
	//
	// is_random_access_iterator_category
	//
	template<typename MaybeCategory>
	struct is_random_access_iterator_category
		: public sprout::is_iterator_category_of<MaybeCategory, std::random_access_iterator_tag>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_CATEGORY_OF_HPP

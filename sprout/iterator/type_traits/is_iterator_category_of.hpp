/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_CATEGORY_OF_HPP
#define SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_CATEGORY_OF_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/type_traits/is_convertible.hpp>

namespace sprout {
	//
	// is_iterator_category_of
	//
	template<typename MaybeCategory, typename Category>
	struct is_iterator_category_of
		: public sprout::is_convertible<MaybeCategory, Category>
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

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename MaybeCategory, typename Category>
	SPROUT_STATIC_CONSTEXPR bool is_iterator_category_of_v = sprout::is_iterator_category_of<MaybeCategory, Category>::value;
	template<typename MaybeCategory>
	SPROUT_STATIC_CONSTEXPR bool is_input_iterator_category_v = sprout::is_input_iterator_category<MaybeCategory>::value;
	template<typename MaybeCategory>
	SPROUT_STATIC_CONSTEXPR bool is_output_iterator_category_v = sprout::is_output_iterator_category<MaybeCategory>::value;
	template<typename MaybeCategory>
	SPROUT_STATIC_CONSTEXPR bool is_forward_iterator_category_v = sprout::is_forward_iterator_category<MaybeCategory>::value;
	template<typename MaybeCategory>
	SPROUT_STATIC_CONSTEXPR bool is_bidirectional_iterator_category_v = sprout::is_bidirectional_iterator_category<MaybeCategory>::value;
	template<typename MaybeCategory>
	SPROUT_STATIC_CONSTEXPR bool is_random_access_iterator_category_v = sprout::is_random_access_iterator_category<MaybeCategory>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_CATEGORY_OF_HPP

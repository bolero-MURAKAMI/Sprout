/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_OF_HPP
#define SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_OF_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/type_traits/is_iterator.hpp>
#include <sprout/iterator/type_traits/is_iterator_category_of.hpp>

namespace sprout {
	namespace detail {
		template<typename MaybeIterator, typename Category, typename = void>
		struct is_iterator_of_impl
			: public std::false_type
		{};
		template<typename MaybeIterator, typename Category>
		struct is_iterator_of_impl<
			MaybeIterator, Category,
			typename std::enable_if<sprout::is_iterator<MaybeIterator>::value>::type
		>
			: public sprout::is_iterator_category_of<typename std::iterator_traits<MaybeIterator>::iterator_category, Category>
		{};
	}	// namespace detail

	//
	// is_iterator_of
	//
	template<typename MaybeIterator, typename Category>
	struct is_iterator_of
		: public sprout::detail::is_iterator_of_impl<MaybeIterator, Category>
	{};

	//
	// is_input_iterator
	//
	template<typename MaybeIterator>
	struct is_input_iterator
		: public sprout::is_iterator_of<MaybeIterator, std::input_iterator_tag>
	{};
	//
	// is_output_iterator
	//
	template<typename MaybeIterator>
	struct is_output_iterator
		: public sprout::is_iterator_of<MaybeIterator, std::output_iterator_tag>
	{};
	//
	// is_forward_iterator
	//
	template<typename MaybeIterator>
	struct is_forward_iterator
		: public sprout::is_iterator_of<MaybeIterator, std::forward_iterator_tag>
	{};
	//
	// is_bidirectional_iterator
	//
	template<typename MaybeIterator>
	struct is_bidirectional_iterator
		: public sprout::is_iterator_of<MaybeIterator, std::bidirectional_iterator_tag>
	{};
	//
	// is_random_access_iterator
	//
	template<typename MaybeIterator>
	struct is_random_access_iterator
		: public sprout::is_iterator_of<MaybeIterator, std::random_access_iterator_tag>
	{};

	//
	// is_iterator_outputable
	//
	template<typename MaybeIterator>
	struct is_iterator_outputable
		: public std::integral_constant<
			bool,
			sprout::is_output_iterator<MaybeIterator>::value || sprout::is_forward_iterator<MaybeIterator>::value
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_OF_HPP

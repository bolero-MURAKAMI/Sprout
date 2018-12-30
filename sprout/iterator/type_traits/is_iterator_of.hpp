/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
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
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace detail {
		template<typename MaybeIterator, typename Category, typename = void>
		struct is_iterator_of_impl
			: public sprout::false_type
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
		: public sprout::bool_constant<
			sprout::is_output_iterator<typename std::decay<MaybeIterator>::type>::value
				|| sprout::is_forward_iterator<typename std::decay<MaybeIterator>::type>::value
		>
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename MaybeIterator, typename Category>
	SPROUT_STATIC_CONSTEXPR bool is_iterator_of_v = sprout::is_iterator_of<MaybeIterator, Category>::value;
	template<typename MaybeIterator>
	SPROUT_STATIC_CONSTEXPR bool is_input_iterator_v = sprout::is_input_iterator<MaybeIterator>::value;
	template<typename MaybeIterator>
	SPROUT_STATIC_CONSTEXPR bool is_output_iterator_v = sprout::is_output_iterator<MaybeIterator>::value;
	template<typename MaybeIterator>
	SPROUT_STATIC_CONSTEXPR bool is_forward_iterator_v = sprout::is_forward_iterator<MaybeIterator>::value;
	template<typename MaybeIterator>
	SPROUT_STATIC_CONSTEXPR bool is_bidirectional_iterator_v = sprout::is_bidirectional_iterator<MaybeIterator>::value;
	template<typename MaybeIterator>
	SPROUT_STATIC_CONSTEXPR bool is_random_access_iterator_v = sprout::is_random_access_iterator<MaybeIterator>::value;
	template<typename MaybeIterator>
	SPROUT_STATIC_CONSTEXPR bool is_iterator_outputable_v = sprout::is_iterator_outputable<MaybeIterator>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_ITERATOR_OF_HPP

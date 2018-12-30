/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_ITERATOR_TRAITS_HPP
#define SPROUT_ITERATOR_ITERATOR_TRAITS_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/utility/pack.hpp>
#include <sprout/detail/nil_base.hpp>

namespace sprout {
	//
	// iterator_traits
	//
	namespace detail {
		template<typename Iterator, typename = void>
		struct iterator_traits_impl
			: public sprout::detail::nil_base
		{};
		template<typename Iterator>
		struct iterator_traits_impl<
			Iterator,
			typename sprout::head_element<
				void,
				typename Iterator::difference_type,
				typename Iterator::value_type,
				typename Iterator::pointer,
				typename Iterator::reference,
				typename Iterator::iterator_category
			>::type
		>
			: public std::iterator_traits<Iterator>
		{};
	}	// namespace detail
	template<typename Iterator>
	struct iterator_traits
		: public sprout::detail::iterator_traits_impl<Iterator>
	{};
	template<typename T>
	struct iterator_traits<T*>
		: public std::iterator_traits<T*>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_ITERATOR_TRAITS_HPP

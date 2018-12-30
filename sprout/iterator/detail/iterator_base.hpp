/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_DETAIL_ITERATOR_BASE_HPP
#define SPROUT_ITERATOR_DETAIL_ITERATOR_BASE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/iterator.hpp>
#include <sprout/utility/use_default.hpp>

namespace sprout {
	namespace detail {
		template<
			typename Iterator,
			typename Category = sprout::use_default,
			typename T = sprout::use_default,
			typename Distance = sprout::use_default,
			typename Pointer = sprout::use_default,
			typename Reference = sprout::use_default
		>
		struct iterator_base
			: public sprout::identity<
				sprout::iterator<
					typename sprout::select_default<Category, typename std::iterator_traits<Iterator>::iterator_category>::type,
					typename sprout::select_default<T, typename std::iterator_traits<Iterator>::value_type>::type,
					typename sprout::select_default<Distance, typename std::iterator_traits<Iterator>::difference_type>::type,
					typename sprout::select_default<Pointer, typename std::iterator_traits<Iterator>::pointer>::type,
					typename sprout::select_default<Reference, typename std::iterator_traits<Iterator>::reference>::type
				>
			>
		{};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_DETAIL_ITERATOR_BASE_HPP

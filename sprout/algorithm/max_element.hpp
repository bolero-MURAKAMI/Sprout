#ifndef SPROUT_ALGORITHM_MAX_ELEMENT_HPP
#define SPROUT_ALGORITHM_MAX_ELEMENT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		template<typename ForwardIterator, typename Compare>
		SPROUT_CONSTEXPR ForwardIterator max_element_impl(
			ForwardIterator first,
			ForwardIterator last,
			Compare comp,
			ForwardIterator max
			)
		{
			return first == last ? max
				: sprout::detail::max_element_impl(sprout::next(first), last, comp, comp(*max, *first) ? first : max)
				;
		}
	}	// namespace detail

	// 25.4.7 Minimum and maximum
	template<typename ForwardIterator, typename Compare>
	SPROUT_CONSTEXPR ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare comp) {
		return sprout::detail::max_element_impl(first, last, comp, first);
	}

	template<typename ForwardIterator>
	SPROUT_CONSTEXPR ForwardIterator max_element(ForwardIterator first, ForwardIterator last) {
		return sprout::max_element(first, last, NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<ForwardIterator>::value_type>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_MAX_ELEMENT_HPP

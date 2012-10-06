#ifndef SPROUT_ALGORITHM_MINMAX_ELEMENT_HPP
#define SPROUT_ALGORITHM_MINMAX_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/pair.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
		minmax_element_impl(
			ForwardIterator first, ForwardIterator last, Compare comp,
			ForwardIterator min, ForwardIterator max
			)
		{
			return first == last ? sprout::pair<ForwardIterator, ForwardIterator>(min, max)
				: comp(*first, *min) ? sprout::detail::minmax_element_impl(sprout::next(first), last, comp, first, max)
				: sprout::detail::minmax_element_impl(sprout::next(first), last, comp, min, comp(*first, *max) ? max : first)
				;
		}
	}	// namespace detail

	// 25.4.7 Minimum and maximum
	template<typename ForwardIterator, typename Compare>
	inline SPROUT_CONSTEXPR pair<ForwardIterator, ForwardIterator>
	minmax_element(ForwardIterator first, ForwardIterator last, Compare comp) {
		return sprout::detail::minmax_element_impl(first, last, comp, first, first);
	}

	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR pair<ForwardIterator, ForwardIterator>
	minmax_element(ForwardIterator first, ForwardIterator last) {
		return sprout::minmax_element(
			first, last,
			NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_MINMAX_ELEMENT_HPP

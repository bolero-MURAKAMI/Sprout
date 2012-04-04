#ifndef SPROUT_ALGORITHM_MIN_ELEMENT_HPP
#define SPROUT_ALGORITHM_MIN_ELEMENT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	namespace detail {
		template<typename ForwardIterator, typename Compare>
		inline SPROUT_CONSTEXPR ForwardIterator min_element_impl(
			ForwardIterator first,
			ForwardIterator last,
			Compare comp,
			ForwardIterator min
			)
		{
			return first == last ? min
				: sprout::detail::min_element_impl(sprout::next(first), last, comp, comp(*first, *min) ? first : min)
				;
		}
	}	// namespace detail

	// 25.4.7 Minimum and maximum
	template<typename ForwardIterator, typename Compare>
	inline SPROUT_CONSTEXPR ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp) {
		return sprout::detail::min_element_impl(first, last, comp, first);
	}

	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator min_element(ForwardIterator first, ForwardIterator last) {
		return sprout::min_element(first, last, NS_SSCRISK_CEL_OR_SPROUT::less<typename std::iterator_traits<ForwardIterator>::value_type>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_MIN_ELEMENT_HPP

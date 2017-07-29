/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_MINMAX_HPP
#define SPROUT_ALGORITHM_MINMAX_HPP

#include <initializer_list>
#include <sprout/config.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/algorithm/minmax_element.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// 25.4.7 Minimum and maximum
	template<typename T, typename Compare>
	inline SPROUT_CONSTEXPR sprout::pair<T const&, T const&>
	minmax(T const& a, T const& b, Compare comp) {
		return comp(b, a) ? sprout::pair<T const&, T const&>(b, a) : sprout::pair<T const&, T const&>(a, b);
	}

	template<typename T>
	inline SPROUT_CONSTEXPR sprout::pair<T const&, T const&>
	minmax(T const& a, T const& b) {
		return sprout::minmax(a, b, NS_SSCRISK_CEL_OR_SPROUT::less<T>());
	}

	namespace detail {
		template<typename T, typename Iterator>
		inline SPROUT_CONSTEXPR sprout::pair<T, T>
		minmax_impl(sprout::pair<Iterator, Iterator> const& p) {
			return sprout::pair<T, T>(*p.first, *p.second);
		}
	}	// namespace detail

	template<typename T, typename Compare>
	inline SPROUT_INITIALIZER_LIST_CONSTEXPR sprout::pair<T, T>
	minmax(std::initializer_list<T> t, Compare comp) {
		return sprout::detail::minmax_impl<T>(sprout::minmax_element(sprout::ptr_index(t.begin(), 0), sprout::ptr_index(t.begin(), t.size()), comp));
	}

	template<typename T>
	inline SPROUT_INITIALIZER_LIST_CONSTEXPR sprout::pair<T, T>
	minmax(std::initializer_list<T> t) {
		return sprout::minmax(t, NS_SSCRISK_CEL_OR_SPROUT::less<T>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_MINMAX_HPP

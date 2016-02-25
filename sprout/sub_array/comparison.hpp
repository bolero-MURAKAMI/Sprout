/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_SUB_ARRAY_COMPARISON_HPP
#define SPROUT_SUB_ARRAY_COMPARISON_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/algorithm/equal.hpp>
#include <sprout/algorithm/lexicographical_compare.hpp>

namespace sprout {
	//
	// operator==
	// operator!=
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return sprout::equal(sprout::begin(lhs), sprout::end(lhs), sprout::begin(rhs));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return sprout::lexicographical_compare(
			sprout::begin(lhs), sprout::end(lhs),
			sprout::begin(rhs), sprout::end(rhs)
			);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return rhs < lhs;
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::sub_array<Container> const& lhs, sprout::sub_array<Container> const& rhs) {
		return !(lhs < rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_SUB_ARRAY_COMPARISON_HPP

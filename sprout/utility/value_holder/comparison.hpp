/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_VALUE_HOLDER_COMPARISON_HPP
#define SPROUT_UTILITY_VALUE_HOLDER_COMPARISON_HPP

#include <sprout/config.hpp>
#include <sprout/utility/compare_pointees.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>

namespace sprout {
	//
	// operator==
	// operator!=
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::value_holder<T> const& lhs, sprout::value_holder<T> const& rhs) {
		return sprout::equal_pointees(lhs, rhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::value_holder<T> const& lhs, sprout::value_holder<T> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::value_holder<T> const& lhs, sprout::value_holder<T> const& rhs) {
		return sprout::less_pointees(lhs, rhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::value_holder<T> const& lhs, sprout::value_holder<T> const& rhs) {
		return rhs < lhs;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::value_holder<T> const& lhs, sprout::value_holder<T> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::value_holder<T> const& lhs, sprout::value_holder<T> const& rhs) {
		return !(lhs < rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_VALUE_HOLDER_COMPARISON_HPP

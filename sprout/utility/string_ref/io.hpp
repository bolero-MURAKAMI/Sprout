/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_STRING_IO_HPP
#define SPROUT_UTILITY_STRING_IO_HPP

#include <iterator>
#include <algorithm>
#include <ios>
#include <sprout/config.hpp>
#include <sprout/utility/string_ref/string_ref.hpp>

namespace sprout {
	//
	// operator<<
	//
	template<typename T, typename Traits, typename StreamTraits>
	inline std::basic_ostream<T, StreamTraits>&
	operator<<(std::basic_ostream<T, StreamTraits>& lhs, sprout::basic_string_ref<T, Traits> const& rhs) {
		std::copy(rhs.begin(), rhs.end(), std::ostreambuf_iterator<T, StreamTraits>(lhs));
		return lhs;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_STRING_IO_HPP

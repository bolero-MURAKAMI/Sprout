/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPTIONAL_MAKE_OPTIONAL_HPP
#define SPROUT_OPTIONAL_MAKE_OPTIONAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/optional/optional.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// make_optional
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::optional<typename std::decay<T>::type>
	make_optional(T&& v) {
		return sprout::optional<typename std::decay<T>::type>(SPROUT_FORWARD(T, v));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::optional<typename std::decay<T>::type>
	make_optional(bool cond, T&& v) {
		return sprout::optional<typename std::decay<T>::type>(cond, SPROUT_FORWARD(T, v));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_MAKE_OPTIONAL_HPP

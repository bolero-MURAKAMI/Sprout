/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VARIANT_GET_HPP
#define SPROUT_VARIANT_GET_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/variant/variant.hpp>

namespace sprout {
	//
	// get
	//
	template<typename T, typename... Types>
	inline SPROUT_CONSTEXPR T const&
	get(sprout::variant<Types...> const& operand) {
		return operand.template get<T>();
	}
	template<typename T, typename... Types>
	inline SPROUT_CONSTEXPR T&
	get(sprout::variant<Types...>& operand) {
		return operand.template get<T>();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_GET_HPP

/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_DEREFERENCE_HPP
#define SPROUT_FUNCTIONAL_DEREFERENCE_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// dereference
	//
	template<typename T = void>
	struct dereference;
	template<>
	struct dereference<void> {
	public:
		typedef void is_transparent;
	public:
		template<typename T>
		SPROUT_CONSTEXPR decltype(*std::declval<T>())
		operator()(T&& x)
		const SPROUT_NOEXCEPT_IF_EXPR(*std::declval<T>())
		{
			return *SPROUT_FORWARD(T, x);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_DEREFERENCE_HPP

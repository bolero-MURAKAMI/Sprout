/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FIXED_CONTAINER_GET_DEEP_INTERNAL_HPP
#define SPROUT_FIXED_CONTAINER_GET_DEEP_INTERNAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/get_internal.hpp>
#include <sprout/container/deep_internal.hpp>
#include <sprout/container/is_sub_container.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace detail {
		template<
			typename Container,
			typename sprout::enabler_if<!sprout::containers::is_sub_container<Container>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::containers::deep_internal<Container>::type
		get_deep_internal_impl(Container&& cont) {
			return SPROUT_FORWARD(Container, cont);
		}
		template<
			typename Container,
			typename sprout::enabler_if<sprout::containers::is_sub_container<Container>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::containers::deep_internal<Container>::type
		get_deep_internal_impl(Container&& cont) {
			return sprout::detail::get_deep_internal_impl(
				sprout::get_internal(SPROUT_FORWARD(Container, cont))
				);
		}
	}	// namespace detail
	//
	// get_deep_internal
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::containers::deep_internal<Container>::type
	get_deep_internal(Container&& cont) {
		return sprout::detail::get_deep_internal_impl(SPROUT_FORWARD(Container, cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_GET_DEEP_INTERNAL_HPP
